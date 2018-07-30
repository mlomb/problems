#include <iostream>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <string.h>
 
using namespace std;
 
typedef long long int lli;
 
const int MAX_N = 10000 + 10;
 
struct Orden {
	int start, end;
	lli price;
};
 
int N;
vector<Orden> orders;
lli dp[MAX_N];
 
int next_order(int time) {
	auto it = lower_bound(orders.begin(), orders.end(), Orden { time, -1, -1 }, [](const Orden& lhs, const Orden& rhs) {
		return lhs.start < rhs.start;
	});
	if(it != orders.end())
		return it - orders.begin() + 1;
	return -1;
}
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
#ifdef LOCAL
	ifstream cin("rent.in");
#endif
	
	int T;
	cin >> T;
	
	for(int i = 0; i < T; i++) {
		cin >> N;
		
		orders.resize(N);
		
		for(int j = 0; j < N; j++) {
			cin >> orders[j].start >> orders[j].end >> orders[j].price;
			orders[j].end += orders[j].start;
		}
		
		sort(orders.begin(), orders.end(), [](const Orden& lhs, const Orden& rhs) {
			return lhs.start < rhs.start;
		});
		
		dp[N + 1] = 0;
		
		for(int k = N; k > 0; k--) {
			Orden& o = orders[k - 1];
			
			lli poniendo = 0;
			
			int next_poniendo = next_order(o.end+1);
			if(next_poniendo != -1)
				poniendo = dp[next_poniendo];
			
			dp[k] = max(o.price + poniendo, dp[k + 1]);
		}
		
		cout << dp[1] << "\n";
	}
	
	
	return 0;
}
