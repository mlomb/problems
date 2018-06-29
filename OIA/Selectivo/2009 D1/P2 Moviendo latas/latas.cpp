#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

typedef long long int lli;

const int MAX_N = 1000 + 10;

int N;
lli best;
lli total;
lli prefixSum[MAX_N][MAX_N * 2];

lli get(int x, int y0, int y1) {
	y0--;
	if (x < 0)
		return 0;

	lli a = 0, b = 0;

	if (y0 > 0)
		a = prefixSum[y0][x];
	y1 = min(y1, N - 1);
	b = prefixSum[y1][x];
	
	return b - a;
}

void test(int x, int y){
	lli accum = 0;

	for (int k = 0; k < N; k++) {
		accum += get(x + k + (N - 1), y, y + (N - k - 1));
	}
	
	best = min(best, total - accum);
}

int main() {
	ifstream cin("latas.in");
	ofstream cout("latas.out");

	cin >> N;

	total = 0;
	lli sumHorz[MAX_N * 2];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i + 1; j++) {
			int x = j + N - 1;
			int y = i;

			if (i == j) sumHorz[x] = 0;
			lli n;
			cin >> n;

			total += n;
			sumHorz[x] += n;
			prefixSum[y][x] = sumHorz[x];
		}
	}

	best = total;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2*N; j++) {
			// considerar este punto como la punta del triangulo
			test(j, i);
		}
	}

	cout << best << endl;

	return 0;
}