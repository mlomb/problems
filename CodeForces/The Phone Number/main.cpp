#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stack>

using namespace std;

typedef long long int lli;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int N;
	cin >> N;
	
	int sq = (int)ceil(sqrt((double)N));
	while(N > sq) {
		for(int i = N - sq + 1; i <= N; i++)
			cout << i << " ";
		N -= sq;
	}
	for(int i = 1; i <= N; i++)
		cout << i << " ";
	cout << endl;
	
	return 0;
}