#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <unordered_map>

using namespace std;

#define LSB(x) (x & (-x))

int N;
unordered_map<int, unordered_map<int, int>> ftree2d;

void add(int x, int y, int amount) {
	for(int xx = x; xx < N; xx += LSB(xx)) {
		for(int yy = y; yy < N; yy += LSB(yy)) {
			ftree2d[xx][yy] += amount;
		}
	}
}

int get(int x, int y) {
	int sum = 0;
	for(int xx = x; xx > 0; xx -= LSB(xx)) {
		for(int yy = y; yy > 0; yy -= LSB(yy)) {
			sum += ftree2d[xx][yy];
		}
	}
	return sum;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
	
	ifstream cin("sumo.in");
#ifndef LOCAL
	ofstream cout("sumo.out");
#endif
	
	int L;
	cin >> L;
	
	vector<pair<int, int>> p;
	p.reserve(L);
	int P, H;
	for(int i = 0; i < L; i++) {
		cin >> P >> H;
		p.emplace_back(P, H);
		N = max(N, max(P, H));
	}
	N++;
	
	for(pair<int, int> luchador : p) {
		add(luchador.first, luchador.second, 1);
	}
	
	for(pair<int, int> luchador : p) {
		cout << (get(luchador.first, luchador.second) - 1) << "\n";
	}
	
	return 0;
}
