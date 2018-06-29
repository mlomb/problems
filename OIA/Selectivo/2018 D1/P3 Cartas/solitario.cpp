#include <vector>
#include <iostream>
#include <math.h>

using namespace std;
long long solve(long long N, const int K) {
	if(N == 1) return 0;
	
	long long jumps = (N + K) / (K + 1);
	long long remaining = N - jumps;
	
	long long res = solve(remaining, K);
	
	long long pos = (jumps * K + res) % remaining;
	
	long long tachadas = pos / K + 1;
	
	return pos + tachadas;
}

int solitario(vector<int> c, long long N, int K) {
	if(K == 0)
		return c[0];
    return c[(N - solve(N, K) - 1) % int(c.size())];
}