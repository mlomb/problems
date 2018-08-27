#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

typedef long long int lli;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	lli N;
	cin >> N;
	
	lli sq = sqrt(N);
	
	for(lli i = sq; i > 0; i--) {
		if(N % i == 0) {
			cout << i << " " << (N / i) << endl;
			return 0;
		}
	}

	return 0;
}