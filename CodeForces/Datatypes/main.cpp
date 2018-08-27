#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int main() {
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int N;
	cin >> N;
	
	vector<int> num;
	for(int i = 0; i < N; i++) {
		int a;
		cin >> a;
		if(a == 1) continue;
		num.push_back(a);
	}
	
	sort(num.begin(), num.end());
	
	int cambia=0;
	for(int i = 0; i < int(num.size()) - 1; i++) {
		int a = num[i];
		int b = num[i + 1];
		
		if(a < b && b < 2*a) {
			cambia=1;
			break;
		}
	}
	cout << (cambia ? "YES" : "NO") << endl;
	
	return 0;
}