#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "../inc/ar_graph.h"
void ar_build_graph(
	struct ar_Graph *g,
	int n, int m,
	int *intput
) {
	g->vertex_count = n;
	g->edge_count = m;

	g->son_count = (int*)malloc(g->vertex_count * sizeof(int));
	memset(g->son_count, 0, g->vertex_count * sizeof(int));

	g->a = (struct ar_Edge**)malloc(g->vertex_count * sizeof(struct ar_Edge*));
	g->data = (struct ar_Edge*)malloc(2 * g->edge_count * sizeof(struct ar_Edge));
	memset(g->data, 0, 2 * g->edge_count * sizeof(struct ar_Edge));
	
	for (int i = 0; i < g->edge_count; i++) {
		g->son_count[intput[i * 3]]++;
		g->son_count[intput[i * 3 + 1]]++;
	}

	g->pos = (int*)malloc(g->vertex_count * sizeof(int));

	g->pos[0] = 0;
	g->a[0] = &(g->data[0]);

	for (int i = 1; i < g->vertex_count; i++) {
		g->pos[i] = g->pos[i - 1] + g->son_count[i - 1];
		g->a[i] = g->a[i - 1] + g->son_count[i - 1];
	}
	
	int *last = (int*)malloc(g->vertex_count * sizeof(int));
	memset(last, 0, g->vertex_count * sizeof(int));

	for (int i = 0; i < g->edge_count; i++) {
		g->a[intput[i * 3]][last[intput[i * 3]]].u = intput[i * 3 + 1];
		g->a[intput[i * 3]][last[intput[i * 3]]].d = intput[i * 3 + 2];

		g->a[intput[i * 3 + 1]][last[intput[i * 3 + 1]]].u = intput[i * 3];
		g->a[intput[i * 3 + 1]][last[intput[i * 3 + 1]]].d = intput[i * 3 + 2];
		
		last[intput[i * 3]]++;
		last[intput[i * 3 + 1]]++;
	}
	
	free(last);
}
void ar_scanf_graph(struct ar_Graph *g) {
	int n, m;
	scanf("%d %d %d", &n, &m, &(g->root));
	g->root--;

	g->edge_count = m;

	int *intput = (int*)malloc(3 * g->edge_count * sizeof(int));
	memset(intput, 0, 3 * g->edge_count * sizeof(int));
	
	for (int i = 0; i < g->edge_count; i++) {
		scanf("%d %d %d", &(intput[i * 3]), &(intput[i * 3 + 1]), &(intput[i * 3 + 2]));
		intput[i * 3]--; intput[i * 3 + 1]--;
	}

	ar_build_graph(g, n, m, intput);

	free(intput);
}
void ar_printf_graph(struct ar_Graph *g) {
	printf("\n");
	printf("%d %d %d\n", g->vertex_count, g->edge_count, g->root + 1);
	for (int i = 0; i < g->vertex_count; i++) {
		printf("%d %d\n", i + 1, g->son_count[i]);
		for (int j = 0; j < g->son_count[i]; j++) {
			if (!g->a[i][j].u && !g->a[i][j].d) {
				printf("\033[1;31m(%d; %d) \033[0m", g->a[i][j].u + 1, g->a[i][j].d);
			} else {
				printf("(%d; %d) ", g->a[i][j].u + 1, g->a[i][j].d);
			}
		}
		printf("\n");
	}
	fflush(stdout);
}
void ar_printf_row_graph(struct ar_Graph *g) {
	printf("%d %d\n", g->vertex_count, g->edge_count);
	int len = 0;
	for (int i = 0; i < g->vertex_count; i++) {
		for (int j = 0; j < g->son_count[i]; j++) {
			if (i < g->a[i][j].u) {
				printf("%d %d %d\n", i + 1, g->a[i][j].u + 1, g->a[i][j].d);
				len += g->a[i][j].d;
			}
		}
	}
	printf("%d\n", len);
	fflush(stdout);
}
void ar_destruct_graph(struct ar_Graph *g) {
	free(g->son_count);
	free(g->a);
	free(g->data);
	free(g->pos);
}
