#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

int m, s;

string r(int nueves, int resto) {
	string s = string(nueves, '9');
	if(resto == 0) {
		s += string(m - nueves, '0');
	} else {
		s += resto + 48;
		s += string(m - (nueves + 1), '0');
	}
	return s;
}

int main() {
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	cin >> m >> s;
	
	if(s > m * 9 ||
	  (s == 0 && m > 1)) {
		cout << "-1 -1" << endl;
		return 0;
	}
	if(m == 1 && s == 0) {
		cout << "0 0" << endl;
		return 0;
	}
	
	// grande
	int nueves = s / 9;
	int resto = s % 9;
	
	//cout << nueves << ", " << resto << endl;
	
	
	string mx = r(nueves, resto);
	string mn = mx;
	reverse(mn.begin(), mn.end());
	
	for(int i = 0; i < mn.size(); i++) {
		if(mn[i] > '0') {
			mn[i]--;
			break;
		}
	}
	mn[0]++;
	
	cout << mn << endl;
	cout << mx << endl;

	return 0;
}