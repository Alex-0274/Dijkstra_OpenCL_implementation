struct ar_Edge{
	int u;
	int d;
};

__kernel void update(
	__global int *dist,
	__global int *upd_dist,
	__global int *avail,
	int vertex_count,
	__global int *updated
) {
	int i = get_global_id(0);
	if (i >= vertex_count) {return;}
	int local_dist = dist[i], new_dist = upd_dist[i];
	if (local_dist > new_dist) {
		dist[i] = new_dist;
		atomic_or(&updated[0], 1);
	}
	avail[i] = local_dist > new_dist;
}

__kernel void dijkstra(
	__global int *pos,
	__global int *son_count,
	__global struct ar_Edge *data,
	__global int *dist,
	__global int *upd_dist,
	__global int *avail,
	int vertex_count
) {
	int v = get_global_id(0);
	if (v >= vertex_count || !avail[v]) {
		return;
	}

	int curent_son_count = son_count[v];
	int local_dist = dist[v];

	struct ar_Edge e;
	int ind, u, d;
	for (ind = 0; ind < curent_son_count; ind++) {
		e = data[pos[v] + ind];
		u = e.u; d = e.d;
		atomic_min(&upd_dist[u], local_dist + d);
	}
}
