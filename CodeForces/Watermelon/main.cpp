#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <string>
#include <sstream>

using namespace std;

int main() {
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int N;
	cin >> N;
	
	if(N % 2 == 0 && N > 2) {
		cout << "YES";
	} else {
		cout << "NO";
	}
	cout << endl;
	
	return 0;
}