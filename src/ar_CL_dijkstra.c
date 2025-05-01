#define CL_TARGET_OPENCL_VERSION 200
#include <string.h>
#include <CL/cl.h>
#include "../inc/ar_graph.h"
#include "../inc/ar_CL_graph_algorithms.h"
#include "../inc/ar_hf.h"
#include "../inc/ar_CL_.h"
int * ar_CL_dijkstra(struct ar_Graph *g) {
	int *dist = (int *)malloc(g->vertex_count * sizeof(int));
	for (int i = 0; i < g->vertex_count; i++) {
		dist[i] = 1000000001;
	}
	dist[g->root] = 0;

	int *avail = (int *)malloc(g->vertex_count * sizeof(int));
	memset(avail, 0, g->vertex_count * sizeof(int));

	avail[g->root] = 1;

	cl_platform_id platform = ar_get_platform();
	cl_device_id device = ar_get_device(&platform);
	cl_context context = ar_get_context(&device);
	cl_command_queue queue = ar_get_command_queue(&context, &device);

	const char *kernel_source = ar_read_file("kernels/dijkstra.cl");

	cl_program program = clCreateProgramWithSource(context, 1, &kernel_source, NULL, NULL);
	clBuildProgram(program, 1, &device, NULL, NULL, NULL);

	cl_kernel kernel = clCreateKernel(program, "dijkstra", NULL);

	cl_mem buffer_Pos, buffer_Son_count, buffer_Data, buffer_Dist, buffer_Avail;
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
	buffer_Avail = clCreateBuffer(
		context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		g->vertex_count * sizeof(int),
		avail,
		NULL
	);

	clSetKernelArg(kernel, 0, sizeof(cl_mem), &buffer_Pos);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), &buffer_Son_count);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), &buffer_Data);
	clSetKernelArg(kernel, 3, sizeof(cl_mem), &buffer_Dist);
	clSetKernelArg(kernel, 4, sizeof(cl_mem), &buffer_Avail);

	while (1) {
		int v = -1;
		for (int i = 0; i < g->vertex_count; i++) {
			if (!avail[i]) {continue;}
			if (v == -1) {v = i; continue;}
			if (dist[i] < dist[v]) {v = i;}
		}
		if (v == -1) {break;}
		clSetKernelArg(kernel, 5, sizeof(int), &v);

		avail[v] = 0;

		clEnqueueWriteBuffer(
			queue,
			buffer_Avail,
			CL_TRUE,
			0,
			g->vertex_count * sizeof(int),
			avail,
			0,
			NULL,
			NULL
		);

		clEnqueueNDRangeKernel(
			queue,
			kernel,
			1,
			NULL,
			(const long unsigned int *)&(g->son_count[v]),
			NULL,
			0,
			NULL,
			NULL
		);

		clFinish(queue);

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

		clEnqueueReadBuffer(
			queue,
			buffer_Avail,
			CL_TRUE,
			0,
			g->vertex_count * sizeof(int),
			avail,
			0,
			NULL,
			NULL
		);
	}

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
