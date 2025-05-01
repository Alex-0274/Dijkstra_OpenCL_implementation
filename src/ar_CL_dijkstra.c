#define CL_TARGET_OPENCL_VERSION 200
#include <string.h>
#include <CL/cl.h>
#include "../inc/ar_graph.h"
#include "../inc/ar_CL_graph_algorithms.h"
#include "../inc/ar_hf.h"
#include "../inc/ar_CL_.h"
int * ar_CL_dijkstra(struct ar_Graph *g) {
	int *dist = (int *)malloc(g->vertex_count * sizeof(int));
	int *upd_dist = (int *)malloc(g->vertex_count * sizeof(int));

	for (int i = 0; i < g->vertex_count; i++) {
		dist[i] = 1000000001;
		upd_dist[i] = 1000000001;
	}
	upd_dist[g->root] = 0;

	int *avail = (int *)malloc(g->vertex_count * sizeof(int));
	memset(avail, 0, g->vertex_count * sizeof(int));

	cl_platform_id platform = ar_get_platform();
	cl_device_id device = ar_get_device(&platform);
	cl_context context = ar_get_context(&device);
	cl_command_queue queue = ar_get_command_queue(&context, &device);

	const char *kernel_source = ar_read_file("kernels/dijkstra.cl");

	cl_program program = clCreateProgramWithSource(context, 1, &kernel_source, NULL, NULL);
	clBuildProgram(program, 1, &device, NULL, NULL, NULL);

	cl_kernel kernel_dijkstra = clCreateKernel(program, "dijkstra", NULL);

	cl_kernel kernel_update = clCreateKernel(program, "update", NULL);

	cl_mem buffer_Pos, buffer_Son_count, buffer_Data, buffer_Dist, buffer_Upd_dist, buffer_Avail;
	buffer_Pos = clCreateBuffer(
		context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		g->vertex_count * sizeof(int),
		g->pos,
		NULL
	);
	buffer_Son_count = clCreateBuffer(
		context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		g->vertex_count * sizeof(int),
		g->son_count,
		NULL
	);
	buffer_Data = clCreateBuffer(
		context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		2 * g->edge_count * sizeof(struct ar_Edge),
		g->data,
		NULL
	);
	buffer_Dist = clCreateBuffer(
		context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		g->vertex_count * sizeof(int),
		dist,
		NULL
	);
	buffer_Upd_dist = clCreateBuffer(
		context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		g->vertex_count * sizeof(int),
		upd_dist,
		NULL
	);
	buffer_Avail = clCreateBuffer(
		context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		g->vertex_count * sizeof(int),
		avail,
		NULL
	);

	clSetKernelArg(kernel_dijkstra, 0, sizeof(cl_mem), &buffer_Pos);
	clSetKernelArg(kernel_dijkstra, 1, sizeof(cl_mem), &buffer_Son_count);
	clSetKernelArg(kernel_dijkstra, 2, sizeof(cl_mem), &buffer_Data);
	clSetKernelArg(kernel_dijkstra, 3, sizeof(cl_mem), &buffer_Dist);
	clSetKernelArg(kernel_dijkstra, 4, sizeof(cl_mem), &buffer_Upd_dist);
	clSetKernelArg(kernel_dijkstra, 5, sizeof(cl_mem), &buffer_Avail);
	clSetKernelArg(kernel_dijkstra, 6, sizeof(int), &g->vertex_count);

	int flag = 1, zero = 0;
	cl_mem buffer_Upd_flag;
	buffer_Upd_flag = clCreateBuffer(
		context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(int),
		&flag,
		NULL
	);

	clSetKernelArg(kernel_update, 0, sizeof(cl_mem), &buffer_Dist);
	clSetKernelArg(kernel_update, 1, sizeof(cl_mem), &buffer_Upd_dist);
	clSetKernelArg(kernel_update, 2, sizeof(cl_mem), &buffer_Avail);
	clSetKernelArg(kernel_update, 3, sizeof(int), &g->vertex_count);
	clSetKernelArg(kernel_update, 4, sizeof(cl_mem), &buffer_Upd_flag);

	while (flag) {

		clEnqueueFillBuffer(
			queue,
			buffer_Upd_flag,
			&zero,
			sizeof(int),
			0,
			sizeof(int),
			0,
			NULL,
			NULL
		);

		clFinish(queue);

		clEnqueueNDRangeKernel(
			queue,
			kernel_update,
			1,
			NULL,
			(const long unsigned int *)&(g->vertex_count),
			NULL,
			0,
			NULL,
			NULL
		);		

		clFinish(queue);

		clEnqueueReadBuffer(
			queue,
			buffer_Upd_flag,
			CL_TRUE,
			0,
			sizeof(int),
			&flag,
			0,
			NULL,
			NULL
		);

		clFinish(queue);

		if (!flag) {break;}

		clEnqueueNDRangeKernel(
			queue,
			kernel_dijkstra,
			1,
			NULL,
			(const long unsigned int *)&(g->vertex_count),
			NULL,
			0,
			NULL,
			NULL
		);

		clFinish(queue);

	}

	clEnqueueReadBuffer(
		queue,
		buffer_Dist,
		CL_TRUE,
		0,
		g->vertex_count * sizeof(int),
		dist,
		0,
		NULL,
		NULL
	);

	free(avail);

	clReleaseDevice(device);
	clReleaseContext(context);
	clReleaseCommandQueue(queue);
	clReleaseMemObject(buffer_Pos);
	clReleaseMemObject(buffer_Data);
	clReleaseMemObject(buffer_Dist);
	clReleaseMemObject(buffer_Avail);
	return dist;
}
