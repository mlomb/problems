#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ifstream cin("mesadas.in");
#ifndef LOCAL
	ofstream cout("mesadas.out");
#endif
	
	int N;
	cin >> N;
	
	vector<pair<int, int>> dims;
	dims.reserve(N);
	
	int a, b;
	for(int i = 0; i < N; i++) {
		cin >> a >> b;
		if(b > a) swap(a, b);
		dims.push_back(make_pair(a, b));
	}
	
	sort(dims.begin(), dims.end());
	
	int mesadas = 1;
	int last = 0;
	for(pair<int, int> dim : dims){
		cout << dim.first << ", " << dim.second << endl;
		int b = dim.second;
		if(b < last) {
			mesadas++;
			last = 0;
		} else
			last = b;
	}
	
	cout << mesadas << endl;
	
	return 0;
}
