#include <bits/stdc++.h>
#include <fstream>
using namespace std;
int main(int argc, char *argv[]) {
	int g, c, i = 0;
	ifstream in_gpu(argv[1]);
	ifstream in_cpu(argv[2]);
	while (in_gpu >> g && in_cpu >> c) {
		if (g != c) {
			cout << "Fail! Dismatch: ";
            cout << i << ' ' << g << ' ' << c << endl;
            return 0;
		}
		++i;
	}
	in_gpu.close();
	in_cpu.close();
    cout << "They are equal!" << endl;
	return 0;
}
