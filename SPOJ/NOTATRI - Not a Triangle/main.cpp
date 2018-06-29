#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	//fstream cin("input.in");
	
	int N;
	cin >> N;
	
	std::vector<int> sticks;
	
	while(N != 0){
		sticks.resize(N);
		for(int i = 0; i < N; i++){
			cin >> sticks[i];
		}
		std::sort(sticks.begin(), sticks.end());
		
		int nonAcceptable = 0;
		for(int i = 0; i < N - 2; i++){
			for(int j = i + 1; j < N - 1; j++){
				//cout << sticks[i] << " ";
				//cout << sticks[j] << " ";
				
				std::vector<int>::iterator ub = upper_bound(sticks.begin() + j + 1, sticks.end(), sticks[i] + sticks[j]);
				nonAcceptable += N - (ub - sticks.begin());
			}
		}
		cout << nonAcceptable << endl;
		
		cin >> N;
	}
	
	return 0;
}
