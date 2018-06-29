#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int N;
	cin >> N;
	
	int cuadrantes[2][2] { { 0, 0 }, { 0, 0 } };
	
	int x, y;
	for(int i = 0; i < N; i++){
		cin >> x >> y;
		cuadrantes[x > 0][y > 0]++;
	}
	
	bool success = cuadrantes[0][0] + cuadrantes[0][1] <= 1 ||
				   cuadrantes[1][0] + cuadrantes[1][1] <= 1;
	
	cout << (success ? "Yes" : "No") << endl;
	
	return 0;
}
