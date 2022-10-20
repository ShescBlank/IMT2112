// Compilation as: gcc -framework OpenCL opencl-id.cpp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

// Create the kernel code in the form of a text string
const char * src =
"__kernel void getmyid(            \n"
"	__global int *a,               \n"
"	__global int *b,               \n"
"	__global int *c,               \n"
"	__global int *d,               \n"
"	__const unsigned int n)        \n"
"{                                 \n"
"	int id = get_global_id(0);     \n"
"	                               \n"
"	if(id < n) {                   \n"
"       a[id] = get_global_id(0);  \n"
"       b[id] = get_local_id(0);   \n"
"       c[id] = get_group_id(0);   \n"
"       d[id] = get_local_size(0); \n"
"   }                              \n"
"}                                 \n"
;

int main() {

    // Allocate the OpenCL variables for the heterogeneous processors
	cl_int err;
	cl_platform_id platform;
	cl_device_id device;
	cl_context ctx;
	cl_command_queue myqueue;

	// Boilerplate functionality
	err = clGetPlatformIDs(1, &platform, NULL);
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_DEFAULT, 1, &device, NULL);
	cl_context_properties cps[3] = { CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0 };
	ctx = clCreateContext(cps, 1, &device, NULL, NULL, &err);
	myqueue = clCreateCommandQueue(ctx, device, 0, &err);

	// Create data on the host
	const unsigned int n = 100;
	printf("Dimension of data: %i\n", n);
    int *h_a = (int *)malloc(sizeof(int) * n);
    int *h_b = (int *)malloc(sizeof(int) * n);
    int *h_c = (int *)malloc(sizeof(int) * n);
    int *h_d = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        h_a[i] = 0;
        h_b[i] = 0;
        h_c[i] = 0;
        h_d[i] = 0;
    }

	// Allocate memory on the device
    cl_mem d_a = clCreateBuffer(ctx, CL_MEM_READ_ONLY, n * sizeof(int), NULL, &err);
    cl_mem d_b = clCreateBuffer(ctx, CL_MEM_READ_ONLY, n * sizeof(int), NULL, &err);
    cl_mem d_c = clCreateBuffer(ctx, CL_MEM_READ_ONLY, n * sizeof(int), NULL, &err);
    cl_mem d_d = clCreateBuffer(ctx, CL_MEM_READ_ONLY, n * sizeof(int), NULL, &err);

	// Initialise on device memory
	// we do not need to initialise since we have only output

    // Create the compute program
	cl_program myprog = clCreateProgramWithSource(ctx, 1, &src, NULL, &err);
	err = clBuildProgram(myprog, 0, NULL, NULL, NULL, NULL);

    // Create the kernel function
    cl_kernel mykernel = clCreateKernel(myprog, "getmyid", &err);

    // Set the arguments of the kernel function
    err = clSetKernelArg(mykernel, 0, sizeof(cl_mem), (void *)&d_a);
    err = clSetKernelArg(mykernel, 1, sizeof(cl_mem), (void *)&d_b);
    err = clSetKernelArg(mykernel, 2, sizeof(cl_mem), (void *)&d_c);
    err = clSetKernelArg(mykernel, 3, sizeof(cl_mem), (void *)&d_d);
    err = clSetKernelArg(mykernel, 4, sizeof(cl_mem), (void *)&n);

    // Execute the kernel in chunks of localSize
	size_t localSize = 16;
    size_t globalSize = (size_t)ceil(n / (float)localSize) * localSize;
//    size_t globalSize = (size_t)n;
    err = clEnqueueNDRangeKernel(myqueue, mykernel, 1, NULL, &globalSize, &localSize, 0, NULL, NULL);
	printf("Local workgroup size: %i\n\n", (int)localSize);
	printf("Glocal workgroup size: %i\n\n", (int)globalSize);

    // Read back the results to the device
    err = clEnqueueReadBuffer(myqueue, d_a, CL_TRUE, 0, n*sizeof(int), (void*)h_a, 0, NULL, NULL);
    err = clEnqueueReadBuffer(myqueue, d_b, CL_TRUE, 0, n*sizeof(int), (void*)h_b, 0, NULL, NULL);
    err = clEnqueueReadBuffer(myqueue, d_c, CL_TRUE, 0, n*sizeof(int), (void*)h_c, 0, NULL, NULL);
    err = clEnqueueReadBuffer(myqueue, d_d, CL_TRUE, 0, n*sizeof(int), (void*)h_d, 0, NULL, NULL);

    // Print the labels
    printf("Global thread IDs:\n");
    for (int i = 0; i < n; i++) {
        printf("%i  ", h_a[i]);
    }
    printf("\n");
    printf("Local thread IDs:\n");
    for (int i = 0; i < n; i++) {
        printf("%i  ", h_b[i]);
    }
    printf("\n");
    printf("Block thread IDs:\n");
    for (int i = 0; i < n; i++) {
        printf("%i  ", h_c[i]);
    }
    printf("\n");
    printf("Local sizes:\n");
    for (int i = 0; i < n; i++) {
        printf("%i  ", h_d[i]);
    }
    printf("\n");
    
    // Shutdown and cleanup
    clReleaseKernel(mykernel);
	clReleaseProgram(myprog);
    clReleaseMemObject(d_a);
    clReleaseMemObject(d_b);
    clReleaseMemObject(d_c);
    clReleaseMemObject(d_d);
	clReleaseCommandQueue(myqueue);
	clReleaseContext(ctx);
	clReleaseDevice(device);
    free(h_a);
    free(h_b);
    free(h_c);
    free(h_d);

	return 0;
}

