#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/ar_graph.h"
#include "../inc/ar_graph_algorithms.h"
int * ar_dijkstra(struct ar_Graph *g) {
	int *dist = (int *)malloc(g->vertex_count * sizeof(int));
	for (int i = 0; i < g->vertex_count; i++) {
		dist[i] = 1000000001;
	}
	dist[g->root] = 0;

	int *avail = (int *)malloc(g->vertex_count * sizeof(int));
	memset(avail, 0, g->vertex_count * sizeof(int));

	avail[g->root] = 1;

	while (1) {
		int v = -1;
		for (int i = 0; i < g->vertex_count; i++) {
			if (!avail[i]) {continue;}
			if (v == -1) {v = i; continue;}
			if (dist[i] < dist[v]) {v = i;}
		}
		if (v == -1) {break;}

		avail[v] = 0;

		int u, d;

		for (int i = 0; i < g->son_count[v]; i++) {
			u = g->a[v][i].u;
			d = g->a[v][i].d;
			if (dist[u] > dist[v] + d) {
				dist[u] = dist[v] + d;
				avail[u] = 1;
			}
		}
	}

	free(avail);

	return dist;
}
