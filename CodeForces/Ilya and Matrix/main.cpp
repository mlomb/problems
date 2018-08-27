#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <string>
#include <map>
#include <sstream>

using namespace std;

typedef long long int lli;


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int N;
	cin >> N;
	
	vector<int> nums(N);
	for(int i = 0; i < N; i++) {
		cin >> nums[i];
	}
	
	sort(nums.begin(), nums.end());
	
	lli resultado = 0;
	int a = 1;
	while(a <= N){
		for(int i = N - 1; i > N - 1 - a; i--) {
			resultado += nums[i];
			//cout<<nums[i]<<endl;
		}
		a *= 4;
	}
	
	cout << resultado << endl;
	
	return 0;
}