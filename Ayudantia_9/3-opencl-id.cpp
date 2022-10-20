// Compilar en Linux: g++ 3-opencl-id.cpp -lOpenCL

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

// Create the kernel code in the form of a text string
// Para correr código en el coprocesador, debemos crear un kernel en formato de string.
// Este kernel contendrá el código a correr (es como un programa extra):
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
// Notar que se define una función que recibe variables (en este caso arrays y un entero), se obtiene el índice global de trabajo
// y, si el id es menor que n, se rellenan los arrays con las estadísticas correspondientes.

// Algo muy importante de notar acá es que los kernels se ejecutan por cada hilo, por lo que realmente el código anterior es un for
// tradicional de toda la vida. Es decir:
// -->      for (int i; i=0, i++) { c[i] = a[i] + b[i]; }
// Es igual a:
// -->      c[id] = a[id] + b[id];

// También es posible notar que como tenemos la condición 'if (id < n)', habrá muchos hilos que ejecuten el código anterior pero que en verdad
// no harán nada, ya que su id está fuera del rango definido por n.


// Ahora sí, vamos con la función principal. Mucho de este código es algo que siempre debemos hacer al utilizar OpenCL
int main() {

    // Allocate the OpenCL variables for the heterogeneous processors
	cl_int err;
	cl_platform_id platform;
	cl_device_id device;
	cl_context ctx;
	cl_command_queue myqueue;

	// Boilerplate functionality
    // Tomamos la plataforma y el dispositivo a utilizar:
	err = clGetPlatformIDs(1, &platform, NULL); // id de la plataforma
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_DEFAULT, 1, &device, NULL); // id del dispositivo
	cl_context_properties cps[3] = { CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0 }; // Creamos un array de propiedades
	ctx = clCreateContext(cps, 1, &device, NULL, NULL, &err); // Creamos un contexto para manejar la memoria del dispositivo
	myqueue = clCreateCommandQueueWithProperties(ctx, device, 0, &err); // Y una cola de comandos

	// Create data on the host
    // Debemos crear la información que utilizaremos en el dispositivo
	const unsigned int n = 100;
	printf("Dimension of data: %i\n", n);
    int* h_a = (int*) calloc(n, sizeof(int));
    int* h_b = (int*) calloc(n, sizeof(int));
    int* h_c = (int*) calloc(n, sizeof(int));
    int* h_d = (int*) calloc(n, sizeof(int));
    // El prefijo h_ lo ponemos para marcar los elementos del host

	// Allocate memory on the device
    // Reservamos la memoria necesaria en el dispositivo (simulando lo que recién creamos)
    cl_mem d_a = clCreateBuffer(ctx, CL_MEM_READ_ONLY, n * sizeof(int), NULL, &err);
    cl_mem d_b = clCreateBuffer(ctx, CL_MEM_READ_ONLY, n * sizeof(int), NULL, &err);
    cl_mem d_c = clCreateBuffer(ctx, CL_MEM_READ_ONLY, n * sizeof(int), NULL, &err);
    cl_mem d_d = clCreateBuffer(ctx, CL_MEM_READ_ONLY, n * sizeof(int), NULL, &err);
    // El prefijo d_ lo ponemos para marcar los elementos del device

	// Initialise on device memory
	// we do not need to initialise since we have only output

    // Create the compute program
	cl_program myprog = clCreateProgramWithSource(ctx, 1, &src, NULL, &err); // Creamos nuestro programa con el kernel (src)
	err = clBuildProgram(myprog, 0, NULL, NULL, NULL, NULL);

    // Create the kernel function
    // Creamos la función definida en el kernel
    cl_kernel mykernel = clCreateKernel(myprog, "getmyid", &err);

    // Set the arguments of the kernel function
    // Seteamos los argumentos que debemos pasarle a la función
    err = clSetKernelArg(mykernel, 0, sizeof(cl_mem), (void *)&d_a);
    err = clSetKernelArg(mykernel, 1, sizeof(cl_mem), (void *)&d_b);
    err = clSetKernelArg(mykernel, 2, sizeof(cl_mem), (void *)&d_c);
    err = clSetKernelArg(mykernel, 3, sizeof(cl_mem), (void *)&d_d);
    err = clSetKernelArg(mykernel, 4, sizeof(cl_mem), (void *)&n);

    // Execute the kernel in chunks of localSize
    // Podemos ejecutar nuestro kernel en distintos tamaños de grupos de trabajo. Independiente del tamaño de trabajo que elijamos,
    // se debe cumplir que el globalSize sea múltiplo de ese tamaño.
    // Por ejemplo: si nuestro localSize=16 y nuestro n=30, entonces nuestro globalSize=32.
    // Notar que los últimos dos hilos ejecutarán código basura ya que no nos importa lo que retornen
	size_t localSize = 16;
    size_t globalSize = (size_t)ceil(n / (float)localSize) * localSize;

    // Ponemos a la cola nuestro kernel para que se ejecute:
    err = clEnqueueNDRangeKernel(myqueue, mykernel, 1, NULL, &globalSize, &localSize, 0, NULL, NULL);
	printf("Local workgroup size: %i\n\n", (int)localSize);
	printf("Glocal workgroup size: %i\n\n", (int)globalSize);

    // Read back the results to the device
    // Pasamos los resultados obtenidos por el coprocesador a nuestras variables que definimos inicialmente:
    err = clEnqueueReadBuffer(myqueue, d_a, CL_TRUE, 0, n*sizeof(int), (void*)h_a, 0, NULL, NULL);
    err = clEnqueueReadBuffer(myqueue, d_b, CL_TRUE, 0, n*sizeof(int), (void*)h_b, 0, NULL, NULL);
    err = clEnqueueReadBuffer(myqueue, d_c, CL_TRUE, 0, n*sizeof(int), (void*)h_c, 0, NULL, NULL);
    err = clEnqueueReadBuffer(myqueue, d_d, CL_TRUE, 0, n*sizeof(int), (void*)h_d, 0, NULL, NULL);

    // Print the labels
    // Printeamos los resultados obtenidos:
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
    // Y debemos limpiar todo lo utilizado (es bastante D:)
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

