#include <bits/stdc++.h>
#define __DeBuG__oK__ {std::cout << "ok" << std::endl; fflush(stdout);}
#define __StOp__ {fflush(stdout); exit(EXIT_SUCCESS);}
#define __SpEeD__iN__oUt__
//#define __MuLtY__tEsT__
using namespace std;
void __ThE__mAiN__sOlUtIoN__(void) {
    int n = 100000 * 1;
    int m = 100000 * 15;
    int root = rand() % n;
    cout << n << ' ' << m << ' ' << root << endl;
    set<pair<int, int>> edge;
    int v, u, d;
    while (int(edge.size()) < m) {
        v = rand() % n + 1;
        u = rand() % n + 1;
        if (v > u) {swap(v, u);}
        if (edge.find({v, u}) == edge.end()) {
            edge.insert({v, u});
        }
        d = rand() % 10000 + 1;
        cout << v << ' ' << u << ' ' << d << endl;
    }
}
void __BeFoR__tHe__MaIn__SoLuTiOn__(void) {}
signed main() {
	srand(time(NULL));
	#ifdef __SpEeD__iN__oUt__
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	#endif
	cout << fixed; cout.precision(20);
	__BeFoR__tHe__MaIn__SoLuTiOn__();
	int __TeSt__CoUnT__ = 1;
	#ifdef __MuLtY__tEsT__
	cin >> __TeSt__CoUnT__;
	#endif
	while (__TeSt__CoUnT__--) {
		__ThE__mAiN__sOlUtIoN__();
	}
	return EXIT_SUCCESS;
}
