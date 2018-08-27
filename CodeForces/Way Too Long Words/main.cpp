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
	
	int N;
	cin >> N;
	
	string s;
	for(int i = 0; i < N; i++) {
		cin >> s;
		if(s.length() <= 10)
			cout << s << endl;
		else {
			cout << s[0] << (s.length() - 2) << s[s.length() - 1] << endl;
		}
	}
	
	return 0;
}