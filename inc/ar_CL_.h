#define CL_TARGET_OPENCL_VERSION 200
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <CL/cl.h>
#ifndef AR_ar_CL_
#define AR_ar_CL_
cl_platform_id ar_get_platform(void);
cl_device_id ar_get_device(cl_platform_id *platform);
cl_context ar_get_context(cl_device_id *device);
cl_command_queue ar_get_command_queue(cl_context *context, cl_device_id *device);
void printf_some_platform_and_device_info(void);
#endif