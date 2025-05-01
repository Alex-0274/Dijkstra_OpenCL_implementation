#define CL_TARGET_OPENCL_VERSION 200
#include <string.h>
#include <CL/cl.h>
#include "../inc/ar_graph.h"
#include "../inc/ar_CL_graph_algorithms.h"
#include "../inc/ar_hf.h"
#include "../inc/ar_CL_.h"
void ar_CL_boruvka(struct ar_Graph *g, struct ar_Graph *mst) {
	// struct ar_disjoint_set set; mst->root = -1;
	
	// ar_init_disjoint_set(&set, g->vertex_count);

	// int *tmp_data, last = 0;
	// tmp_data = (int *)malloc(3 * (g->vertex_count - 1) * sizeof(int));
	// memset(tmp_data, 0, 3 * (g->vertex_count - 1) * sizeof(int));

	// int *min_edge;
	// min_edge = (int *)malloc(2 * g->vertex_count * sizeof(int));
	
	// cl_platform_id platform = ar_get_platform();
	// cl_device_id device = ar_get_device(&platform);
	// cl_context context = ar_get_context(&device);
	// cl_command_queue queue = ar_get_command_queue(&context, &device);

	// const char *kernel_source = ar_read_file("kernels/boruvka.cl");

	// cl_program program = clCreateProgramWithSource(context, 1, &kernel_source, NULL, NULL);
	// clBuildProgram(program, 1, &device, NULL, NULL, NULL);

	// cl_kernel kernel = clCreateKernel(program, "boruvka", NULL);

	// cl_mem buffer_Pos, buffer_Son_count, buffer_Data, buffer_Dist, buffer_Avail;
	// buffer_Pos = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, g->vertex_count * sizeof(int), g->pos, NULL);
	// buffer_Son_count = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, g->vertex_count * sizeof(int), g->son_count, NULL);
	// buffer_Data = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, 2 * g->edge_count * sizeof(struct ar_Edge), g->data, NULL);
	// buffer_Dist = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, g->vertex_count * sizeof(int), dist, NULL);
	// buffer_Avail = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, g->vertex_count * sizeof(int), avail, NULL);

	// while (last < g->vertex_count - 2) {
	// 	memset(min_edge, 0, 2 * g->vertex_count * sizeof(int));
	// 	for (int v = 0; v < g->vertex_count; v++) {
	// 		for (int i = 0; i < g->son_count[v]; i++) {
	// 			int u = g->a[v][i].u;
	// 			int d = g->a[v][i].d;
	// 			if (
	// 				ar_parent_disjoint_set_unit(&set.element[v]) !=
	// 				ar_parent_disjoint_set_unit(&set.element[u])
	// 			) {
	// 				if (!min_edge[v * 2 + 1] || min_edge[v * 2 + 1] > d) {
	// 					min_edge[v * 2] = u;
	// 					min_edge[v * 2 + 1] = d;
	// 				}
	// 				if (!min_edge[u * 2 + 1] || min_edge[u * 2 + 1] > d) {
	// 					min_edge[u * 2] = v;
	// 					min_edge[u * 2 + 1] = d;
	// 				}
	// 			}
	// 		}
	// 	}

	// 	for (int v = 0; v < g->vertex_count; v++) {
	// 		int u = min_edge[v * 2];
	// 		int d = min_edge[v * 2 + 1];
	// 		if (
	// 			ar_parent_disjoint_set_unit(&set.element[v]) !=
	// 			ar_parent_disjoint_set_unit(&set.element[u])
	// 		) {
	// 			ar_union_disjoint_set(&set.element[v], &set.element[u]);
	// 			tmp_data[last * 3] = v;
	// 			tmp_data[last * 3 + 1] = u;
	// 			tmp_data[last * 3 + 2] = d;
	// 			last++;
	// 		}
	// 	}
	// }

	// ar_build_graph(mst, g->vertex_count, g->vertex_count - 1, tmp_data);

	// free(tmp_data);
	// free(min_edge);
	// ar_destruct_disjoint_set(&set);

	// clReleaseDevice(device);
	// clReleaseContext(context);
	// clReleaseCommandQueue(queue);
}
