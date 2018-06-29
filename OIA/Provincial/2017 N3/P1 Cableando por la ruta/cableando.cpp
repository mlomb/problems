#include <iostream>
#include <limits.h>

using namespace std;

int main() {
	long long N, K;
	
	cin >> N >> K;
	
	long long c;
	long long min = 0, max = 0;
	for(int i = 0; i < N; i++) {
		cin >> c;
		
		c -= K;
		
		if(c < min){
			min = c;
		} else if(c > max){
			max = c;
		}
	}
	
	//cout << min << ", " << max << endl;
	
	long long diff = (max - min);
	if(diff < 0)
		diff += diff * 2;
	
	cout << diff << endl;

	return 0;
}