#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <string>
#include <sstream>

using namespace std;

int main() {
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int N;
	cin >> N;
	
	vector<int> nums(N);
	for(int i = 0; i < N; i++) {
		cin >> nums[i];
	}
	
	vector<int> nums_ord = nums;
	sort(nums_ord.begin(), nums_ord.end());
	
	vector< pair<int, int> > res;
	
	for(int i = 0; i < N; i++) {
		int j = i;
		for(; j < N; j++) {
			if(nums_ord[i] == nums[j])
				break;
		}
		if(i == j) continue;
		swap(nums[i], nums[j]);
		res.push_back(make_pair(i, j));
	}
	
	cout << res.size() << endl;
	for(pair<int, int> p : res) {
		cout << p.first << " " << p.second << endl;
	}
	
	return 0;
}