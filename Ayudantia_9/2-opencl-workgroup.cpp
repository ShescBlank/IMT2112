// Compilation as: gcc -framework OpenCL opencl-workgroup.cpp

#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif


int main() {

	cl_int err;
    cl_platform_id platform;
    cl_device_id device;

    // Get platform and device
	clGetPlatformIDs(1, &platform, NULL);
	clGetDeviceIDs(platform, CL_DEVICE_TYPE_DEFAULT, 1, &device, NULL);
    // Change the second argument in: CL_DEVICE_TYPE_DEFAULT, CL_DEVICE_TYPE_ALL, CL_DEVICE_TYPE_CPU, CL_DEVICE_TYPE_GPU

    // print device name
    size_t valueSize;
    clGetDeviceInfo(device, CL_DEVICE_NAME, 0, NULL, &valueSize);
    char* value = (char*) malloc(valueSize);
    clGetDeviceInfo(device, CL_DEVICE_NAME, valueSize, value, NULL);
    printf("Device name: %s\n", value);
    free(value);
    
    
    // print size of work group
    
	size_t max_work_group_size = -1;
	clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &max_work_group_size, NULL);
    printf("Maximum work group size for this device: %i\n", (int)max_work_group_size );

	cl_uint max_work_item_dims = -1;
	clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), &max_work_item_dims, NULL);
    printf("Maximum work item dimensions: %i\n", (int)max_work_item_dims );

	size_t max_work_item_sizes[9];
	clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(max_work_item_sizes), max_work_item_sizes, NULL);
	for (int i = 0; i < max_work_item_dims; ++i) {
        printf("Workgroup size along dim: %i: %i\n", i, (int)max_work_item_sizes[i] );
    }

	return 0;
}
