#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int N, K;
	cin >> N >> K;
	
	int i = 1;
	int last;
	
	cout << 1 << " ";
	last = 1;
	int l = 1;
	
	for(int k = K; k > 0; k--) {
		int dif = (k * l) + last;
		cout << dif << " ";
		last = dif;
		l *= -1;
		i++;
	}
	
	for(i++; i <= N; i++) {
		cout << i << " ";
	}
	cout << endl;
	
	return 0;
}