#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef long long int lli;

#define MAX 10000000 * 2 + 10

lli dp[MAX];

int main() {

	// precompute
	dp[1] = 0;
	for(lli i = 2; i < MAX; i++){
		lli steps = dp[i - 1];
		
		if(i % 2 == 0 && dp[i / 2] < steps)
			steps = dp[i / 2];
		if(i % 3 == 0 && dp[i / 3] < steps)
			steps = dp[i / 3];
		
		dp[i] = steps + 1;
	}
	
	//ifstream cin("input.in");
	
	int T;
	cin >> T;
	
	lli n;
	for(int i = 0; i < T; i++){
		cin >> n;
		cout << "Case " << (i + 1) << ": " << dp[n] << endl;
	}
	
	return 0;
}
