#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

typedef long double ld;
typedef long long int lli;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#else
	freopen("drunkard.in", "r", stdin);
	freopen("drunkard.out", "w", stdout);
#endif
	
	int P, Q;
	
	while(cin >> P >> Q) {
		if(P == 0 && Q == 0) break;
		cout << 257 << endl;
		for(int i = 1; i < 128; i++) {
			cout << (2*i) << " " << (2*i+1) << endl;
		}
		for(int i = 128; i < 256-Q; i++) {
			cout << 1 << " " << i << endl;
		}
		for(int i = 256-Q; i < 256-P; i++) {
			cout << i << " " << 257 << endl;
		}
		for(int i = 256-P; i < 256; i++) {
			cout << i << " " << 256 << endl;
		}
	}
	
	return 0;
}