// Compilation as: gcc -framework OpenCL opencl-id-2d.cpp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cassert>

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
"	__global int *e,               \n"
"	__global int *f,               \n"
"	__global int *g,               \n"
"	__global int *h,               \n"
"	__global int *i,               \n"
"	__global int *j,               \n"
"	__const unsigned int n)        \n"
"{                                 \n"
"	int row = get_global_id(0);    \n"
"	int col = get_global_id(1);    \n"
"	int el = col + row * n;        \n"
"	                               \n"
"	if(row < n && col < n) {       \n"
"       a[el] = get_global_id(0);  \n"
"       b[el] = get_local_id(0);   \n"
"       c[el] = get_group_id(0);   \n"
"       d[el] = get_local_size(0); \n"
"       e[el] = get_num_groups(0); \n"
"       f[el] = get_global_id(1);  \n"
"       g[el] = get_local_id(1);   \n"
"       h[el] = get_group_id(1);   \n"
"       i[el] = get_local_size(1); \n"
"       j[el] = get_num_groups(1); \n"
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
	err = clGetPlatformIDs(1, &platform, NULL); assert(err == 0);
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL); assert(err == 0);
	cl_context_properties cps[3] = { CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0 };
	ctx = clCreateContext(cps, 1, &device, NULL, NULL, &err); assert(err == 0);
	myqueue = clCreateCommandQueue(ctx, device, 0, &err); assert(err == 0);

    // print device name
    size_t valueSize;
    err = clGetDeviceInfo(device, CL_DEVICE_NAME, 0, NULL, &valueSize); assert(err == 0);
    char* value = (char*) malloc(valueSize);
    err = clGetDeviceInfo(device, CL_DEVICE_NAME, valueSize, value, NULL); assert(err == 0);
    printf("Device name: %s\n", value);
    free(value);
    
	// Create data on the host
    const unsigned int nRow = 8;
    const unsigned int nCol = 8;
    const unsigned int nMat = nRow*nCol;
    int *h_a = (int *)malloc(sizeof(int) * nMat);
    int *h_b = (int *)malloc(sizeof(int) * nMat);
    int *h_c = (int *)malloc(sizeof(int) * nMat);
    int *h_d = (int *)malloc(sizeof(int) * nMat);
    int *h_e = (int *)malloc(sizeof(int) * nMat);
    int *h_f = (int *)malloc(sizeof(int) * nMat);
    int *h_g = (int *)malloc(sizeof(int) * nMat);
    int *h_h = (int *)malloc(sizeof(int) * nMat);
    int *h_i = (int *)malloc(sizeof(int) * nMat);
    int *h_j = (int *)malloc(sizeof(int) * nMat);
    for (int i = 0; i < nMat; i++) {
        h_a[i] = 0;
        h_b[i] = 0;
        h_c[i] = 0;
        h_d[i] = 0;
        h_e[i] = 0;
        h_f[i] = 0;
        h_g[i] = 0;
        h_h[i] = 0;
        h_i[i] = 0;
        h_j[i] = 0;
    }

	// Allocate memory on the device
    cl_mem d_a = clCreateBuffer(ctx, CL_MEM_READ_ONLY, nMat * sizeof(int), NULL, &err); assert(err == 0);
    cl_mem d_b = clCreateBuffer(ctx, CL_MEM_READ_ONLY, nMat * sizeof(int), NULL, &err); assert(err == 0);
    cl_mem d_c = clCreateBuffer(ctx, CL_MEM_READ_ONLY, nMat * sizeof(int), NULL, &err); assert(err == 0);
    cl_mem d_d = clCreateBuffer(ctx, CL_MEM_READ_ONLY, nMat * sizeof(int), NULL, &err); assert(err == 0);
    cl_mem d_e = clCreateBuffer(ctx, CL_MEM_READ_ONLY, nMat * sizeof(int), NULL, &err); assert(err == 0);
    cl_mem d_f = clCreateBuffer(ctx, CL_MEM_READ_ONLY, nMat * sizeof(int), NULL, &err); assert(err == 0);
    cl_mem d_g = clCreateBuffer(ctx, CL_MEM_READ_ONLY, nMat * sizeof(int), NULL, &err); assert(err == 0);
    cl_mem d_h = clCreateBuffer(ctx, CL_MEM_READ_ONLY, nMat * sizeof(int), NULL, &err); assert(err == 0);
    cl_mem d_i = clCreateBuffer(ctx, CL_MEM_READ_ONLY, nMat * sizeof(int), NULL, &err); assert(err == 0);
    cl_mem d_j = clCreateBuffer(ctx, CL_MEM_READ_ONLY, nMat * sizeof(int), NULL, &err); assert(err == 0);

	// Initialise on device memory
	// we do not need to initialise since we have only output

    // Create the compute program
	cl_program myprog = clCreateProgramWithSource(ctx, 1, &src, NULL, &err); assert(err == 0);
	err = clBuildProgram(myprog, 0, NULL, NULL, NULL, NULL); assert(err == 0);

    // Create the kernel function
    cl_kernel mykernel = clCreateKernel(myprog, "getmyid", &err); assert(err == 0);

    // Set the arguments of the kernel function
    err = clSetKernelArg(mykernel, 0, sizeof(cl_mem), (void *)&d_a); assert(err == 0);
    err = clSetKernelArg(mykernel, 1, sizeof(cl_mem), (void *)&d_b); assert(err == 0);
    err = clSetKernelArg(mykernel, 2, sizeof(cl_mem), (void *)&d_c); assert(err == 0);
    err = clSetKernelArg(mykernel, 3, sizeof(cl_mem), (void *)&d_d); assert(err == 0);
    err = clSetKernelArg(mykernel, 4, sizeof(cl_mem), (void *)&d_e); assert(err == 0);
    err = clSetKernelArg(mykernel, 5, sizeof(cl_mem), (void *)&d_f); assert(err == 0);
    err = clSetKernelArg(mykernel, 6, sizeof(cl_mem), (void *)&d_g); assert(err == 0);
    err = clSetKernelArg(mykernel, 7, sizeof(cl_mem), (void *)&d_h); assert(err == 0);
    err = clSetKernelArg(mykernel, 8, sizeof(cl_mem), (void *)&d_i); assert(err == 0);
    err = clSetKernelArg(mykernel, 9, sizeof(cl_mem), (void *)&d_j); assert(err == 0);
    err = clSetKernelArg(mykernel, 10, sizeof(cl_mem), (void *)&nCol); assert(err == 0);

    // Execute the kernel in chunks of localSize
    size_t localSizes[2] = { 4 , 2 };
    size_t globalSizes[2] = { (size_t)ceil(nRow / (float)localSizes[0]) * localSizes[0] , (size_t)ceil(nCol / (float)localSizes[1]) * localSizes[1] };
    printf("Local sizes: %i %i\n", (int)localSizes[0], (int)localSizes[1]);
    printf("Global sizes: %i %i\n", (int)globalSizes[0], (int)globalSizes[1]);
    err = clEnqueueNDRangeKernel(myqueue, mykernel, 2, NULL, globalSizes, localSizes, 0, NULL, NULL); assert(err == 0);
    
    // Read back the results to the device
    err = clEnqueueReadBuffer(myqueue, d_a, CL_TRUE, 0, nMat*sizeof(int), (void*)h_a, 0, NULL, NULL); assert(err == 0);
    err = clEnqueueReadBuffer(myqueue, d_b, CL_TRUE, 0, nMat*sizeof(int), (void*)h_b, 0, NULL, NULL); assert(err == 0);
    err = clEnqueueReadBuffer(myqueue, d_c, CL_TRUE, 0, nMat*sizeof(int), (void*)h_c, 0, NULL, NULL); assert(err == 0);
    err = clEnqueueReadBuffer(myqueue, d_d, CL_TRUE, 0, nMat*sizeof(int), (void*)h_d, 0, NULL, NULL); assert(err == 0);
    err = clEnqueueReadBuffer(myqueue, d_e, CL_TRUE, 0, nMat*sizeof(int), (void*)h_e, 0, NULL, NULL); assert(err == 0);
    err = clEnqueueReadBuffer(myqueue, d_f, CL_TRUE, 0, nMat*sizeof(int), (void*)h_f, 0, NULL, NULL); assert(err == 0);
    err = clEnqueueReadBuffer(myqueue, d_g, CL_TRUE, 0, nMat*sizeof(int), (void*)h_g, 0, NULL, NULL); assert(err == 0);
    err = clEnqueueReadBuffer(myqueue, d_h, CL_TRUE, 0, nMat*sizeof(int), (void*)h_h, 0, NULL, NULL); assert(err == 0);
    err = clEnqueueReadBuffer(myqueue, d_i, CL_TRUE, 0, nMat*sizeof(int), (void*)h_i, 0, NULL, NULL); assert(err == 0);
    err = clEnqueueReadBuffer(myqueue, d_j, CL_TRUE, 0, nMat*sizeof(int), (void*)h_j, 0, NULL, NULL); assert(err == 0);

    // Print the labels
    printf("Global thread IDs dim0:\n");
    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            int elem = j+i*nCol;
            printf("%i  ", h_a[j+i*nCol]);
        }
        printf("\n");
    }
    printf("Local thread IDs dim0:\n");
    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            int elem = j+i*nCol;
            printf("%i  ", h_b[j+i*nCol]);
        }
        printf("\n");
    }
    printf("Block thread IDs dim0:\n");
    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            int elem = j+i*nCol;
            printf("%i  ", h_c[j+i*nCol]);
        }
        printf("\n");
    }
    printf("Local sizes dim0:\n");
    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            int elem = j+i*nCol;
            printf("%i  ", h_d[j+i*nCol]);
        }
        printf("\n");
    }
    printf("Number of groups dim0:\n");
    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            int elem = j+i*nCol;
            printf("%i  ", h_e[j+i*nCol]);
        }
        printf("\n");
    }
    printf("Global thread IDs dim1:\n");
    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            int elem = j+i*nCol;
            printf("%i  ", h_f[j+i*nCol]);
        }
        printf("\n");
    }
    printf("Local thread IDs dim1:\n");
    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            int elem = j+i*nCol;
            printf("%i  ", h_g[j+i*nCol]);
        }
        printf("\n");
    }
    printf("Block thread IDs dim1:\n");
    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            int elem = j+i*nCol;
            printf("%i  ", h_h[j+i*nCol]);
        }
        printf("\n");
    }
    printf("Local sizes dim1:\n");
    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            int elem = j+i*nCol;
            printf("%i  ", h_i[j+i*nCol]);
        }
        printf("\n");
    }
    printf("Number of groups dim1:\n");
    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            int elem = j+i*nCol;
            printf("%i  ", h_j[j+i*nCol]);
        }
        printf("\n");
    }

    // Shutdown and cleanup
    clReleaseKernel(mykernel);
	clReleaseProgram(myprog);
    clReleaseMemObject(d_a);
    clReleaseMemObject(d_b);
    clReleaseMemObject(d_c);
    clReleaseMemObject(d_d);
    clReleaseMemObject(d_e);
    clReleaseMemObject(d_f);
    clReleaseMemObject(d_g);
    clReleaseMemObject(d_h);
    clReleaseMemObject(d_i);
    clReleaseMemObject(d_j);
	clReleaseCommandQueue(myqueue);
	clReleaseContext(ctx);
	clReleaseDevice(device);
    free(h_a);
    free(h_b);
    free(h_c);
    free(h_d);
    free(h_e);
    free(h_f);
    free(h_g);
    free(h_h);
    free(h_i);
    free(h_j);

	return 0;
}

