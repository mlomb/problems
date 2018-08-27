#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <strings.h>

using namespace std;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif

	int T, V, E;
	cin >> T;
	
	for(int i = 0; i < T; i++) {
		cin >> V >> E;
		cout << (2 + E - V) << endl;
	}


	return 0;
}