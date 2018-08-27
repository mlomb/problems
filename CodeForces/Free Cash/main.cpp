#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

int c[100000];

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int N;
	cin >> N;
	for(int i = 0; i < N; i++) {
		int h, m;
		cin >> h >> m;
		int t = h * 60 + m;
		c[t]++;
	}
	
	int mx = 0;
	for(int i = 0; i < 100000; i++) {
		mx = max(mx, c[i]);
	}
	
	cout << mx << endl;

	return 0;
}