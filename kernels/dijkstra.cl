struct ar_Edge{
	int u;
	int d;
};

__kernel void best_vertex(

) {

}

__kernel void dijkstra(
	__global int *pos,
	__global int *son_count,
	__global struct ar_Edge *data,
	__global int *dist,
	__global int *avail,
	int v
) {
	int id = get_global_id(0);
	if (id >= son_count[v]) {
		return;
	}

	struct ar_Edge e = data[pos[v] + id];
	int parent_dist = dist[v];
	int u = e.u, d = e.d;

	if (dist[u] > parent_dist + d) {
		dist[u] = parent_dist + d;
		avail[u] = 1;
	}
}
