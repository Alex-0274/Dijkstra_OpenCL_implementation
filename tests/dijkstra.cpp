#include <bits/stdc++.h>
using namespace std;
const int INF = 1000000001;
int n, m;
int start;
vector<vector<pair<int, int>>> a;
vector<int> d;
void dijkstra(void) {
	d.resize(n, INF);
	d[start] = 0;
	set<pair<int, int>> q;
	q.insert(make_pair(0, start));
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());
		for (size_t i = 0; i < a[v].size(); i++) {
			int to = a[v][i].first;
			int len = a[v][i].second;
			if (d[to] > d[v] + len) {
				q.erase(make_pair(d[to], to));
				d[to] = d[v] + len;
				q.insert(make_pair(d[to], to));
			}
		}
	}
}
int main() {
	cin >> n >> m >> start;
	--start;
	a.resize(n, vector<pair<int, int>> ());
	for (int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		--x; --y;
		a[x].push_back(make_pair(y, z));
		a[y].push_back(make_pair(x, z));
	}
	dijkstra();
	for (int i = 0; i < n; i++) {
		cout << d[i] << ' ';
	}
	cout << endl;
	return 0;
}

