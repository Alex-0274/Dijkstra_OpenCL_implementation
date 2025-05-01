#include <malloc.h>
#include <string.h>
#include "../inc/ar_graph.h"
#include "../inc/ar_disjoint_set.h"
#include "../inc/ar_graph_algorithms.h"
void ar_boruvka(struct ar_Graph *g, struct ar_Graph *mst) {
	struct ar_disjoint_set set; mst->root = -1;
	
	ar_init_disjoint_set(&set, g->vertex_count);

	int *tmp_data, last = 0;
	tmp_data = (int *)malloc(3 * (g->vertex_count - 1) * sizeof(int));
	memset(tmp_data, 0, 3 * (g->vertex_count - 1) * sizeof(int));

	int *min_edge;
	min_edge = (int *)malloc(2 * g->vertex_count * sizeof(int));
	
	while (last < g->vertex_count - 2) {
		memset(min_edge, 0, 2 * g->vertex_count * sizeof(int));
		for (int v = 0; v < g->vertex_count; v++) {
			for (int i = 0; i < g->son_count[v]; i++) {
				int u = g->a[v][i].u;
				int d = g->a[v][i].d;
				if (
					ar_parent_disjoint_set_unit(&set.element[v]) !=
					ar_parent_disjoint_set_unit(&set.element[u])
				) {
					if (!min_edge[v * 2 + 1] || min_edge[v * 2 + 1] > d) {
						min_edge[v * 2] = u;
						min_edge[v * 2 + 1] = d;
					}
					if (!min_edge[u * 2 + 1] || min_edge[u * 2 + 1] > d) {
						min_edge[u * 2] = v;
						min_edge[u * 2 + 1] = d;
					}
				}
			}
		}

		for (int v = 0; v < g->vertex_count; v++) {
			int u = min_edge[v * 2];
			int d = min_edge[v * 2 + 1];
			if (
				ar_parent_disjoint_set_unit(&set.element[v]) !=
				ar_parent_disjoint_set_unit(&set.element[u])
			) {
				ar_union_disjoint_set(&set.element[v], &set.element[u]);
				tmp_data[last * 3] = v;
				tmp_data[last * 3 + 1] = u;
				tmp_data[last * 3 + 2] = d;
				last++;
			}
		}
	}

	ar_build_graph(mst, g->vertex_count, g->vertex_count - 1, tmp_data);

	free(tmp_data);
	free(min_edge);
	ar_destruct_disjoint_set(&set);
}
