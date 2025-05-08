#include <bits/stdc++.h>
#include <fstream>
using namespace std;
int main(int argc, char *argv[]) {
	int g, c, i = 0;
	ifstream in_gpu(argv[1]);
	ifstream in_cpu(argv[2]);
	while (in_gpu >> g && in_cpu >> c) {
		if (g != c) {
			printf("\033[1;31mFail! Dismatch: \033[0m");
			printf("\033[1;33m%d %d %d\033[0m\n", i, g, c);
            return 0;
		}
		++i;
	}
	in_gpu.close();
	in_cpu.close();
	printf("\033[1;34mThey are equal!\033[0m\n");
	return 0;
}
