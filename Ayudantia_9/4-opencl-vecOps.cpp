// Compilar en Linux: g++ 4-opencl-vecOps.cpp -lOpenCL

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
"__kernel void vecadd(         \n"
"	__global float *a,         \n"
"	__global float *b,         \n"
"	__global float *c,         \n"
"	__const unsigned int n)    \n"
"{                             \n"
"	int id = get_global_id(0); \n"
"	if(id < n){                \n"
"		c[id] = a[id] + b[id]; \n"
"   }                          \n"
"}                             \n"
"__kernel void vecmul(         \n"
"	__global float *a,         \n"
"	__global float *b,         \n"
"	__global float *c,         \n"
"	__const unsigned int n)    \n"
"{                             \n"
"	int id = get_global_id(0); \n"
"	if(id < n){                \n"
"		c[id] = a[id] * b[id]; \n"
"   }                          \n"
"}                             \n"
;

// Ahora, en este kernel creamos dos funciones, una para sumar vectores y otra para multiplicarlos

int main() {

    // Allocate the OpenCL variables for the heterogeneous processors
    cl_int err;
    cl_platform_id platform;
    cl_device_id device;
    cl_context ctx;
    cl_command_queue myqueue;

    // Boilerplate functionality
    // Repetimos el mismo procedimiento que para el código anterior:
    err = clGetPlatformIDs(1, &platform, NULL);
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    cl_context_properties cps[3] = { CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0 };
    ctx = clCreateContext(cps, 1, &device, NULL, NULL, &err);
    myqueue = clCreateCommandQueueWithProperties(ctx, device, 0, &err);

    // Create data on the host
    const unsigned int n = 100;
    float *h_a = (float *)malloc(sizeof(float) * n);
    float *h_b = (float *)malloc(sizeof(float) * n);
    float *h_c = (float *)malloc(sizeof(float) * n);
    float *h_d = (float *)malloc(sizeof(float) * n);
    for (int i = 0; i < n; i++) {
        h_a[i] = 0.5f*i;
        h_b[i] = (float)n - 0.5f*i;
    }

    // Print the vectors
    printf("a = [");
    for (int i = 0; i < n; i++) {
        printf("%.1f  ", h_a[i]);
    }
    printf("]\n");
    printf("b = [");
    for (int i = 0; i < n; i++) {
        printf("%.1f  ", h_b[i]);
    }
    printf("]\n");

    // Allocate memory on the device
    cl_mem d_a = clCreateBuffer(ctx, CL_MEM_READ_ONLY, n * sizeof(float), NULL, &err);
    cl_mem d_b = clCreateBuffer(ctx, CL_MEM_READ_ONLY, n * sizeof(float), NULL, &err);
    cl_mem d_c = clCreateBuffer(ctx, CL_MEM_READ_ONLY, n * sizeof(float), NULL, &err);
    cl_mem d_d = clCreateBuffer(ctx, CL_MEM_READ_ONLY, n * sizeof(float), NULL, &err);

    // Initialise on device memory
    err = clEnqueueWriteBuffer(myqueue, d_a, CL_TRUE, 0, n * sizeof(float), (void*)h_a, 0, NULL, NULL);
    err = clEnqueueWriteBuffer(myqueue, d_b, CL_TRUE, 0, n * sizeof(float), (void*)h_b, 0, NULL, NULL);
    // the variable c does not need to be initialised since it is where results are written to
    // Básicamente agregamos a la cola un comando para escribir en un objeto buffer desde memoria del host
    // Por eso les pasamos h_a y h_b para rellenar d_a y d_b.
    // Notar que d_c y d_d no es necesario llenarlos.

    // Create the compute program
    // Creamos nuestro programa con el kernel
    cl_program myprog = clCreateProgramWithSource(ctx, 1, &src, NULL, &err);
    err = clBuildProgram(myprog, 0, NULL, NULL, NULL, NULL);

    // Create the kernel function
    // Debemos crear las dos funciones que hay en el kernel
    cl_kernel mykernelAdd = clCreateKernel(myprog, "vecadd", &err);
    cl_kernel mykernelMul = clCreateKernel(myprog, "vecmul", &err);

    // Set the arguments of the kernel function
    // Rellenamos los argumentos de ambas funciones con nuestro objetos del device
    clSetKernelArg(mykernelAdd, 0, sizeof(cl_mem), (void *)&d_a);
    clSetKernelArg(mykernelAdd, 1, sizeof(cl_mem), (void *)&d_b);
    clSetKernelArg(mykernelAdd, 2, sizeof(cl_mem), (void *)&d_c);
    clSetKernelArg(mykernelAdd, 3, sizeof(unsigned int), (void *)&n);

    clSetKernelArg(mykernelMul, 0, sizeof(cl_mem), (void *)&d_a);
    clSetKernelArg(mykernelMul, 1, sizeof(cl_mem), (void *)&d_b);
    clSetKernelArg(mykernelMul, 2, sizeof(cl_mem), (void *)&d_d);
    clSetKernelArg(mykernelMul, 3, sizeof(unsigned int), (void *)&n);

    // Execute the kernel in chunks of localSize
    size_t localSize = 8;
    size_t globalSize = (size_t)ceil(n / (float)localSize) * localSize;
    err = clEnqueueNDRangeKernel(myqueue, mykernelAdd, 1, NULL, &globalSize, &localSize, 0, NULL, NULL);
    err = clEnqueueNDRangeKernel(myqueue, mykernelMul, 1, NULL, &globalSize, &localSize, 0, NULL, NULL);
    
    // Read back the results to the device
    err = clEnqueueReadBuffer(myqueue, d_c, CL_TRUE, 0, n*sizeof(float), (void*)h_c, 0, NULL, NULL);
    err = clEnqueueReadBuffer(myqueue, d_d, CL_TRUE, 0, n*sizeof(float), (void*)h_d, 0, NULL, NULL);

    // Print the vectors
    printf("c = a+b = [");
    for (int i = 0; i < n; i++) {
        printf("%.1f  ", h_c[i]);
    }
    printf("]\n");
    printf("d = a*b = [");
    for (int i = 0; i < n; i++) {
        printf("%.2f  ", h_d[i]);
    }
    printf("]\n");

    // Compute the error of the kernel addition
    float maxerr = 0.0f;
    for (int i = 0; i < n; i++) {
        float newerr = fabs(h_a[i] + h_b[i] - h_c[i]);
        if (newerr > maxerr)
            maxerr = newerr;
    }
    printf("Maximum error: %f\n", maxerr);

    // Compute the error of the kernel multiplication
    maxerr = 0.0f;
    for (int i = 0; i < n; i++) {
        float newerr = fabs(h_a[i] * h_b[i] - h_d[i]);
        if (newerr > maxerr)
            maxerr = newerr;
    }
    printf("Maximum error: %f\n", maxerr);
    
    // Shutdown and cleanup
    clReleaseKernel(mykernelAdd);
    clReleaseKernel(mykernelMul);
    clReleaseProgram(myprog);
    clReleaseMemObject(d_d);
    clReleaseMemObject(d_c);
    clReleaseMemObject(d_b);
    clReleaseMemObject(d_a);
    clReleaseCommandQueue(myqueue);
    clReleaseContext(ctx);
    clReleaseDevice(device);
    free(h_d);
    free(h_c);
    free(h_b);
    free(h_a);

    return 0;
}

