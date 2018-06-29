#include <iostream>
#include <vector>
#include <math.h>
#include <queue>
#include <strings.h>
#include <fstream>
#include <bitset>
#include <unistd.h>

using namespace std;

const int MAX_MASK = 65535 + 100;
const int INF = 999999999;

int N, K;
int best_cercado[MAX_MASK];
int dp[MAX_MASK];
int mask_max;

int solve(int mask) {
	if(mask == 0)
		return best_cercado[mask];
	if(dp[mask] != INF)
		return dp[mask];
	
	//cout << " ----------- Mask: " << bitset<3>(mask) << " -----------" << endl;
	
	for(int i = 1; i <= mask; i++){
		int a = mask ^ i;
		if((a | mask) == mask) {
			//cout << "i: " << bitset<3>(i) << ", a: " << bitset<3>(a) << endl;
			
			dp[mask] = min(dp[mask], best_cercado[i] + solve(a));
		}
	}
	
	return dp[mask];
}

int main() {
	ifstream fin("placas.in");
	ofstream cout("placas.out");
	
	fin >> K >> N;
	
	mask_max = (1 << N) - 1;
	
	for(int i = 0; i <= mask_max; i++)
		dp[i] = INF;
	
	vector< pair<int, int> > pts;
	
	int x, y;
	for(int i = 0; i < N; i++){
		fin >> x >> y;
		pts.push_back({ x, y });
	}
	
	for(int i = 1; i <= mask_max; i++) {
		int mask = i;
		int minx = INF, maxx = -INF, miny = INF, maxy = -INF;
		while(mask > 0) {
			int id = mask & (-mask);
			int pos = __builtin_ctz(id);
			
			minx = min(minx, pts[pos].first - K);
			maxx = max(maxx, pts[pos].first + K);
			
			miny = min(miny, pts[pos].second - K);
			maxy = max(maxy, pts[pos].second + K);
			
			mask -= id;
		}
		best_cercado[i] = 2 * (maxx - minx) + 2 * (maxy - miny);
	}
	
	cout << solve(mask_max) << endl;
	
	return 0;
}
