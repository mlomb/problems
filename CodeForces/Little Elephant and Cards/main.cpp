#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

typedef unsigned long long int lli;

const int INF = 99999999;

int N;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	cin >> N;
	
	int half = (N + 1) / 2;
	
	map<int, int> occ;
	map<int, int> occ_front;
	int a, b;
	for(int i = 0; i < N; i++) {
		cin >> a >> b;
		occ[a]++;
		if(a != b)
			occ[b]++;
		occ_front[a]++;
	}
	
	int mn = INF;
	for(auto& p : occ) {
		if(p.second >= half) {
			int delta = half - occ_front[p.first];
			if(delta <= 0) {
				cout << 0 << endl;
				return 0;
			}
			mn = min(mn, delta);
		}
	}
	
	if(mn == INF)
		cout << -1 << endl;
	else
		cout << mn << endl;
	
	return 0;
}