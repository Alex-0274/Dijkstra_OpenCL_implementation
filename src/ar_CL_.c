#define CL_TARGET_OPENCL_VERSION 200
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <CL/cl.h>
cl_platform_id ar_get_platform(void) {
	cl_platform_id platform;
	clGetPlatformIDs(1, &platform, NULL);
	return platform;
} 
cl_device_id ar_get_device(cl_platform_id *platform) {
	cl_device_id device;
	clGetDeviceIDs(*platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
	return device;
}
cl_context ar_get_context(cl_device_id *device) {
	return clCreateContext(NULL, 1, device, NULL, NULL, NULL);
}
cl_command_queue ar_get_command_queue(cl_context *context, cl_device_id *device) {
	return (cl_command_queue)clCreateCommandQueueWithProperties(*context, *device, 0, NULL);
}
void printf_some_platform_and_device_info(void) {
	cl_platform_id platform; clGetPlatformIDs(1, &platform, NULL);
	printf("\e[35m┌Platform\e[39m:\n");

	size_t platform_profile_size; char *platform_profile;
	clGetPlatformInfo(platform, CL_PLATFORM_PROFILE, 0, NULL, &platform_profile_size);
	platform_profile = (char*)malloc(platform_profile_size);
	clGetPlatformInfo(platform, CL_PLATFORM_PROFILE, platform_profile_size, platform_profile, NULL);
	printf("\e[33m├Profile\e[39m: \e[36m%s\e[39m\n", platform_profile); free(platform_profile);

	size_t platform_name_size; char *platform_name;
	clGetPlatformInfo(platform, CL_PLATFORM_NAME, 0, NULL, &platform_name_size);
	platform_name = (char*)malloc(platform_name_size);
	clGetPlatformInfo(platform, CL_PLATFORM_NAME, platform_name_size, platform_name, NULL);
	printf("\e[33m├Name\e[39m: \e[36m%s\e[39m\n", platform_name); free(platform_name);

	size_t platform_vendor_size; char *platform_vendor;
	clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, 0, NULL, &platform_vendor_size);
	platform_vendor = (char*)malloc(platform_vendor_size);
	clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, platform_vendor_size, platform_vendor, NULL);
	printf("\e[33m├Vendor\e[39m: \e[36m%s\e[39m\n", platform_vendor); free(platform_vendor);

	size_t platform_version_size; char *platform_version;
	clGetPlatformInfo(platform, CL_PLATFORM_VERSION, 0, NULL, &platform_version_size);
	platform_version = (char*)malloc(platform_version_size);
	clGetPlatformInfo(platform, CL_PLATFORM_VERSION, platform_version_size, platform_version, NULL);
	printf("\e[33m├Version\e[39m: \e[36m%s\e[39m\n", platform_version); free(platform_version);

	size_t platform_extensions_size; char *platform_extensions;
	clGetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS, 0, NULL, &platform_extensions_size);
	platform_extensions = (char*)malloc(platform_extensions_size);
	clGetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS, platform_extensions_size, platform_extensions, NULL);
	printf("\e[33m└Extensions\e[39m: \e[36m%s\e[39m\n", platform_extensions); free(platform_extensions);

	cl_device_id device; clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
	printf("\e[35m┌Device\e[39m:\n");

	size_t device_name_size = 0; char *device_name;
	clGetDeviceInfo(device, CL_DEVICE_NAME, 0, NULL, &device_name_size);
	device_name = (char*)malloc(device_name_size);
	clGetDeviceInfo(device, CL_DEVICE_NAME, device_name_size, device_name, NULL);
	printf("\e[33m├Name\e[39m: \e[36m%s\e[39m\n", device_name); free(device_name);

	size_t device_vendor_size = 0; char *device_vendor;
	clGetDeviceInfo(device, CL_DEVICE_VENDOR, 0, NULL, &device_vendor_size);
	device_vendor = (char*)malloc(device_vendor_size);
	clGetDeviceInfo(device, CL_DEVICE_VENDOR, device_vendor_size, device_vendor, NULL);
	printf("\e[33m├Vendor\e[39m: \e[36m%s\e[39m\n", device_vendor);  free(device_vendor);

	size_t device_version_size = 0; char *device_version;
	clGetDeviceInfo(device, CL_DEVICE_VERSION, 0, NULL, &device_version_size);
	device_version = (char*)malloc(device_version_size);
	clGetDeviceInfo(device, CL_DEVICE_VERSION, device_version_size, device_version, NULL);
	printf("\e[33m├Version\e[39m: \e[36m%s\e[39m\n", device_version); free(device_version);

	size_t device_extensions_size = 0; char *device_extensions;
	clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, 0, NULL, &device_extensions_size);
	device_extensions = (char*)malloc(device_extensions_size);
	clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, device_extensions_size, device_extensions, NULL);
	printf("\e[33m├extensions\e[39m: \e[36m%s\e[39m\n", device_extensions); free(device_extensions);

	cl_int device_max_compute_units;
	clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_int), &device_max_compute_units, NULL);
	printf("\e[33m├Max compute units\e[39m: \e[36m%d\e[39m\n", device_max_compute_units);

	cl_int device_max_work_item_dimensions;
	clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_int), &device_max_work_item_dimensions, NULL);
	printf("\e[33m├Device max work item dimensions\e[39m: \e[36m%d\e[39m\n", device_max_work_item_dimensions);

	size_t *device_max_work_item_sizes = (size_t*)malloc(device_max_work_item_dimensions * sizeof(size_t));
	clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, device_max_work_item_dimensions * sizeof(size_t), device_max_work_item_sizes, NULL);
	printf("\e[33m├Device max work item sizes\e[39m: \e[36m");
	for (int i = 0; i < device_max_work_item_dimensions; i++) {printf("%d ", device_max_work_item_sizes[i]);}
	printf("\e[39m\n"); free(device_max_work_item_sizes);

	cl_int device_max_work_group_size;
	clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(cl_int), &device_max_work_group_size, NULL);
	printf("\e[33m├Max work group size\e[39m: \e[36m%d\e[39m\n", device_max_work_group_size);

	cl_int device_max_clock_frequency;
	clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_int), &device_max_clock_frequency, NULL);
	printf("\e[33m└Max clock frequency\e[39m: \e[36m%dMHz\e[39m\n", device_max_clock_frequency);
}