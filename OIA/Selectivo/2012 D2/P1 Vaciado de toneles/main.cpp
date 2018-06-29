#include <iostream>
#include <fstream>

using namespace std;

const int MAX_N = 1000000 + 10;

int toneles[MAX_N];

int main() {
	ifstream cin("toneles.in");
#ifndef LOCAL
	ofstream cout("toneles.out");
#endif

	int L, N;
	cin >> L >> N;

	int first_non_zero = -1;
	for (int i = 0; i < N; i++){
		cin >> toneles[i];
		if(first_non_zero == -1 && toneles[i] > 0)
			first_non_zero = i;
	}

	int sum = 0;
	int movs = 0;
	
	int i = first_non_zero;
	int j = i;
	
	for (; i < N; i++){
		if(sum + toneles[i] > L) {
			movs += N - j;
			sum = toneles[i];
			j = i;
		} else
			sum += toneles[i];
	}
	if(sum > 0)
		movs += N - j;

	cout << movs << " " << (j + 1) << endl;

	return 0;
}
