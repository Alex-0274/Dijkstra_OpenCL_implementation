#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed; cout.precision(20);
	
	int n, m, root, v, u, d;
	set<pair<int, int>> edge;
	
	vector<int> arg(argc - 1);
	
	for (int i = 1; i < argc; i++) {
		arg[i - 1] = stoi(argv[i]);
	}

	n = arg[1]; m = n * arg[2];

	srand(time(NULL) + arg[0]);

	root = rand() % n;

	cout << n << ' ' << m << ' ' << root << endl;

	while (int(edge.size()) < m) {

		v = rand() % n + 1;
		u = rand() % n + 1;
		
		if (u == v) {continue;}

		if (v > u) {
			swap(v, u);
		}

		if (edge.find({v, u}) == edge.end()) {
			edge.insert({v, u});
		} else {
			continue;
		}

		d = rand() % 1000 + 1;

		cout << v << ' ' << u << ' ' << d << endl;

	}

	return 0;
}
