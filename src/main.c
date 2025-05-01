#define CL_TARGET_OPENCL_VERSION 200
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <CL/cl.h>
#include "../inc/ar_graph.h"
#include "../inc/ar_disjoint_set.h"
#include "../inc/ar_graph_algorithms.h"
#include "../inc/ar_CL_graph_algorithms.h"
int main(void) {
	struct ar_Graph g;
	ar_scanf_graph(&g);

	int *dist = ar_CL_dijkstra(&g);

	ar_destruct_graph(&g);
	free(dist);
	return 0;
}
