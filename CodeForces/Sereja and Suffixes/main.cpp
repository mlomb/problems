#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef long long int lli;

#define MAX 100001
lli nums[MAX];
lli dp[MAX];
bool seen[MAX];

int main() {
	//ifstream cin("input.in");
	
	lli N, M;
	cin >> N >> M;
	
	for(int i = 0; i < N; i++)
		cin >> nums[i];
	
	dp[N] = 0;	
	for(int i = N - 1; i >= 0; i--){
		dp[i] = dp[i + 1] + !seen[nums[i]];
		seen[nums[i]] = true;
	}
	
	lli l;
	for(int i = 0; i < M; i++){
		cin >> l;
		cout << dp[l - 1] << endl;
	}
	
	return 0;
}
