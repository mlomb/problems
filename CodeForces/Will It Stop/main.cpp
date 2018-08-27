#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

typedef long long int lli;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	lli N;
	cin >> N;
	
	lli i = 1;
	for(; i <= N; i *= 2) {
		if(i == N) {
			cout << "TAK" << endl;
			return 0;
		}
	}
	cout << "NIE" << endl;
	
	return 0;
}