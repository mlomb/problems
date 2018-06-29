#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int OFF = 5;

struct Estado {
	int mx;
	int sum;
	
	bool operator<(const Estado& other) const {
		if(mx == other.mx)
			return sum < other.sum;
		return mx < other.mx;
	}
};

Estado dp[1000000 + OFF];
int nums[2][1000000 + OFF];

void solve(const int index, const int N, int* tot, int* not_used){
	if(N < 1) return;
	else if(N == 1) {
		*not_used += nums[index][OFF];
		return;
	}
	else if(N == 2) {
		*tot += nums[index][OFF] * nums[index][OFF + 1];
		return;
	}
	
	for(int i = 0; i < OFF; i++)
		dp[i] = { 0, 0 };
	
	for(int i = 0; i < N; i++){
		dp[i + OFF] = max(Estado { dp[i + OFF - 2].mx + nums[index][i + OFF] * nums[index][i + OFF - 1], dp[i + OFF - 2].sum },
						  Estado { dp[i + OFF - 1].mx, 													 dp[i + OFF - 1].sum + nums[index][i + OFF] });
	}
	
	*tot += dp[OFF + N - 1].mx;
	*not_used += dp[OFF + N - 1].sum;
	
	/*
	for(int i = 0; i < N + OFF; i++) cout << nums[index][i + OFF] << " ";
	cout << endl;
	cout << "***********" << endl;
	for(int i = 0; i < N + OFF; i++) cout << dp[i].mx << " ";
	cout << endl;
	for(int i = 0; i < N + OFF; i++) cout << dp[i].sum << " ";
	cout << endl;
	cout << "-------------" << endl;
	*/
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	ifstream fin("maxinum.in");
	
	int N;
	fin >> N;
	
	for(int i = 0; i < N; i++){
		int n;
		fin >> n;
		nums[i % 2][i / 2 + OFF] = n;
	}
	
	int tot = 0, not_used = 0;
	solve(0, (N + 1) / 2, &tot, &not_used);
	solve(1, N / 2, &tot, &not_used);
	
	ofstream fout("maxinum.out");
	
	fout << tot << endl;
	fout << not_used << endl;
	
	return 0;
}
