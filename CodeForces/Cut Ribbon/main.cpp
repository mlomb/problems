#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	//ifstream cin("input.in");
	
	int n, a, b, c;
	cin >> n >> a >> b >> c;
	
	vector<int> arr;
	arr.push_back(a);
	arr.push_back(b);
	arr.push_back(c);
	
	sort(arr.begin(), arr.end());
	
	// cabeza
	a = arr[0];
	b = arr[1];
	c = arr[2];
	int max_a = n / a;
	int max_b = n / b;
	int max_c = n / c;
	
	if(n % a == 0) {
		cout << max_a << endl;
	} else {
		int mx = 0;
		for(int x = 0; x <= max_a; x++) {
			for(int y = 0; y <= max_b; y++) {
				for(int z = 0; z <= max_c; z++) {
					int k = a * x + b * y + c * z;
					int cant = x + y + z;
					if(k == n) {
						mx = max(mx, cant);
					} else if(k > n) 
						break;
				}
			}
		}
		cout << mx << endl;
	}
	
	return 0;
}