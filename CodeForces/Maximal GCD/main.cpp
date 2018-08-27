#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

typedef long long int lli;
const lli INF = 9999999999;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	lli N, K;
	cin >> N >> K;
	
	if(K > 10e6) {
		cout << -1 << endl;
		return 0;
	}
	
	lli s = ((K + 1) * K) / 2;
	
	if(N < s) {
		cout << -1 << endl;
		return 0;
	}
	
	lli max_gcd = N / s;
	
	//cout << s << ", " << max_gcd << endl;
	
	lli sqn = sqrt(N);
	
	if(max_gcd < sqn) {
		for(; max_gcd >= 1; max_gcd--) {
			if(N % max_gcd == 0)
				break;
		}
	} else {
		bool primo = true;
		for(lli i = 1; i < 2 * sqn + 3; i++) {
			if(N % i == 0 && N / i <= max_gcd) {
				max_gcd = N / i;
				primo = false;
				break;
			}
		}
		if(primo) {
			max_gcd = sqn;
			for(; max_gcd >= 1; max_gcd--) {
				if(N % max_gcd == 0)
					break;
			}
		}
	}
	
	//cout << "max_gcd after: " << max_gcd << endl;
	
	// max_gcd
	lli sum = 0;
	
	for(lli i = 0; i < K - 1; i++) {
		lli num = (i+1) * max_gcd;
		sum += num;
		cout << num << " ";
	}
	cout << (N - sum) << endl;
	
	return 0;
}