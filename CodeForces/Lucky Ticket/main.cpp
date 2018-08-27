#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

typedef unsigned long long int lli;

const int INF = 99999999;

bool lucky(string s) {
	for(char& c : s) {
		if(c != '4' && c != '7')
			return false;
	}
	return true;
}

bool sums(string s) {
	int a = 0, b = 0;
	int i = 0;
	for(; i < int(s.length()) / 2; i++) {
		a += s[i] - '0';
	}
	for(; i < int(s.length()); i++) {
		b += s[i] - '0';
	}
	return a == b;
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int N;
	string num;
	cin >> N >> num;
	
	cout << (lucky(num) && sums(num) ? "YES" : "NO") << endl;
	
	
	return 0;
}