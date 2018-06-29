#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	ifstream cin("maraton.in");
	ofstream cout("maraton.out");

	int A;
	cin >> A;

	vector<int> cat(10 + 5, 0);

	int N, C;
	for (int i = 0; i < A; i++){
		cin >> N >> C;
		if (cat[C] == 0)
			cat[C] = N;
	}

	for (int i = 1; i <= 10; i++){
		cout << i << " " << cat[i] << endl;
	}

	return 0;
}