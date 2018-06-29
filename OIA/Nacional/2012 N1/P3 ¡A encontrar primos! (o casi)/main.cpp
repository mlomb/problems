#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

const int MAX_N = 10000000 + 10;

int main() {
	ifstream cin("casi-primo.in");
#ifndef LOCAL
	ofstream cout("casi-primo.out");
#endif

	int a, b, c;
	cin >> a >> b >> c;

	bitset<MAX_N> nums;
	nums.set();
	
	nums[0] =  nums[1] = 0;
	
	for(int i = 0; i < a; i++) nums[i] = 0;
	for(int i = b + 1; i < MAX_N; i++) nums[i] = 0;
	
	// criba parcial
	for(int k = 2; k <= c; k++){
		for(int i = k; i <= b; i += k){
			nums[i] = 0;
		}
	}
	
	cout << nums.count() << endl;
	
	return 0;
}
