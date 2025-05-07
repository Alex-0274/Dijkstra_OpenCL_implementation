#define CL_TARGET_OPENCL_VERSION 200
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <CL/cl.h>
#include "../inc/ar_graph.h"
#include "../inc/ar_disjoint_set.h"
#include "../inc/ar_graph_algorithms.h"
#include "../inc/ar_CL_graph_algorithms.h"
int main(void) {
	srand(time(NULL));
	struct ar_Graph g;
	ar_scanf_graph(&g);

	g.root = rand() % g.vertex_count;
	printf("%d\n", g.root);

	int *dist = ar_CL_dijkstra(&g);

	// for (int i = 0; i < g.vertex_count; i++) {
		// printf("%d ", dist[i]);
	// }
	// printf("\n");

	ar_destruct_graph(&g);
	free(dist);
	return 0;
}
