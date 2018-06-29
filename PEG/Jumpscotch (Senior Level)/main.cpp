#include <iostream>
#include <vector>
#include <fstream>
#include <deque>

using namespace std;

int main() {
	//ifstream cin("input.in");
	
	int N, d;
	cin >> N >> d;
	
	vector<int> nums(N);
	for(int i = 0; i < N; i++)
		cin >> nums[i];
	
	deque<int> dominantes; // best, pos
	dominantes.push_back(nums[0]);
	
	for(int j = 1; j < N; j++){
		int n = nums[j];
		
		if(j >= d){
			if(!dominantes.empty() && dominantes.front() == nums[j - d - 1])
				dominantes.pop_front();
		}
		
		int best = dominantes.front() + n;
		nums[j] = best;
		
		while(!dominantes.empty() && dominantes.back() > best)
			dominantes.pop_back();
		dominantes.push_back(best);
	}
	
	cout << nums.back() << endl;

	return 0;
}
