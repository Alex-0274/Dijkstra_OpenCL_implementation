#ifndef AR_ar_graph
#define AR_ar_graph
struct ar_Edge{
	int u;
	long long d;
};

struct ar_Graph{
	int vertex_count;
	int edge_count;
	int root;
	int *son_count;
    struct ar_Edge **a;
	struct ar_Edge *data;
	int *pos;
};

void ar_build_graph(
	struct ar_Graph *g,
	int n, int m,
	int *tmp
);

void ar_scanf_graph(struct ar_Graph *g);

void ar_printf_graph(struct ar_Graph *g);

void ar_printf_row_graph(struct ar_Graph *g);

void ar_destruct_graph(struct ar_Graph *g);
#endif