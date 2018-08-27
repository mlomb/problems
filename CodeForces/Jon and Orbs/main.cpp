#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef long double ld;

const int MAX_N = 1000 + 10;
const ld E = 10e-7;

ld dp[2][MAX_N];

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	ld K, Q; // K-types, Q-queries
	cin >> K >> Q;
	
	for(int i = 0; i < K; i++)
		dp[0][i] = 0;
	dp[0][0] = 1;
	
	priority_queue< pair<int, int> > queries;
	
	for(int i = 0; i < Q; i++) {
		int p;
		cin >> p;
		queries.push(make_pair(-p, i));
	}
	
	vector<int> result(Q);
	
	for(int i = 0; i < 100000000; i++) { // ith-day
		
		/*
		for(int j = 0; j < K; j++) {
			cout << dp[i % 2][int(K) - j - 1] << " ";
		}
		cout << endl;
		*/
		
		while(queries.size() > 0 && ((-queries.top().first) - E)/2000.0 < dp[i % 2][int(K) - 1]) {
			result[queries.top().second] = i + 1;
			queries.pop();
		}
		
		if(queries.size() == 0)
			break;
		
		
		for(int j = 0; j < K; j++) {
			ld sum = 0;
			
			if(j)
				sum += dp[i % 2][j - 1] * ((K - j) / K); // diag
			
			sum += dp[i % 2][j] * ((j + 1) / K); // izq
			
			dp[(i + 1) % 2][j] = sum;
		}
	}
	
	for(int r : result) {
		cout << r << endl;
	}
	
	return 0;
}