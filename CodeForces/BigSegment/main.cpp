#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

typedef long long int lli;
const lli INF = 9999999999;

int main() {
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int N;
	cin >> N;
	
	lli mx_dist = -1, mx_l = INF, mx_r = -INF;
	int mx_dist_ind;
	lli mx_dist_start;
	lli a, b;
	
	for(int i = 0; i < N; i++) {
		cin >> a >> b;
		mx_l = min(mx_l, a);
		mx_r = max(mx_r, b);
		
		lli d = b - a;
		if(d > mx_dist) {
			mx_dist = d;
			mx_dist_start = a;
			mx_dist_ind = i;
		}
	}
	
	if(mx_dist_start <= mx_l && mx_dist_start + mx_dist >= mx_r) {
		cout << mx_dist_ind+1 << endl;
	} else {
		cout << -1 << endl;
	}
	
	
	return 0;
}