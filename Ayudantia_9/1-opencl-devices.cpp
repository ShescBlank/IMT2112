// Compilar en Linux: g++ 1-opencl-devices.cpp -lOpenCL

// Includes generales
#include <stdio.h>
#include <stdlib.h>

// Hacemos un if para los include, en caso de que estemos en un dispositivo Apple o Linux
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

// Empezamos con nuestra función main
int main() {

    // Declaramos algunas variables que necesitaremos:
    int i, j;
    char* value;
    size_t valueSize;
    cl_uint platformCount;
    cl_platform_id* platforms;
    cl_uint deviceCount;
    cl_device_id* devices;
    cl_uint maxComputeUnits;

    // Queremos ver todas las plataformas que tenemos disponibles:
    clGetPlatformIDs(0, NULL, &platformCount); // Obtenemos la cantidad de plataformas
    platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * platformCount); // Hacemos un array para guardar los ids de las plataformas
    clGetPlatformIDs(platformCount, platforms, NULL); // Guardamos sus ids en el array

    // Recorremos las plataformas para obtener su información:
    for (i = 0; i < platformCount; i++) 
    {
        // Agarramos todos los dispositivos de esta plataforma:
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
        devices = (cl_device_id*) malloc(sizeof(cl_device_id) * deviceCount); // Nuevamente reservamos un array, ahora para guardar los dispositivos
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);

        // E imprimimos la información de cada uno
        for (j = 0; j < deviceCount; j++)
        {
            // print device name
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, valueSize, value, NULL);
            printf("%d. Device: %s\n", j+1, value);
            free(value);

            // print hardware device version
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, valueSize, value, NULL);
            printf(" %d.%d Hardware version: %s\n", j+1, 1, value);
            free(value);

            // print software driver version
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, valueSize, value, NULL);
            printf(" %d.%d Software version: %s\n", j+1, 2, value);
            free(value);

            // print c version supported by compiler for device
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, valueSize, value, NULL);
            printf(" %d.%d OpenCL C version: %s\n", j+1, 3, value);
            free(value);

            // print parallel compute units
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS,
                    sizeof(maxComputeUnits), &maxComputeUnits, NULL);
            printf(" %d.%d Parallel compute units: %d\n", j+1, 4, maxComputeUnits);

        }

        // Liberamos el array de los dispositivos
        free(devices);
    }

    // Liberamos el array de las plataformas
    free(platforms);

    // Retornamos
    return 0;
}