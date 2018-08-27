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

	int N;
	char ss[1000 + 10];

	cin >> N;
	cin.ignore();
	
	string s;
	for(int i = 0; i < N; i++) {
		cin.getline(ss, 1000 + 10);
		s = string(ss);
		
		map<char, int> c;
		for(int i = 0; i < int(s.length()); i++) {
			if(s[i] == ' ') continue;
			c[s[i]]++;
		}
		
		pair<char, int> mx = make_pair('?', -1);
		for(pair<char, int> p : c) {
			if(p.second > mx.second) {
				mx = p;
			}
		}
		
		// check repeated
		// max apparitions
		int apparitions = 0;
		for(pair<char, int> p : c) {
			if(p.second == mx.second) {
				apparitions++;
			}
		}
		
		if(apparitions == 1) {
			int off = (('E' - mx.first) + 26) % 26;
			
			int dist = 0;
			for(int k = 'E'; k < 100; k++) {
				if((k - 'A') % 26 + 'A' == mx.first)
					break;
				dist++;
			}
			
			cout << dist << " ";
			//cout << abs(mx.first - 'E') << " ";
			
			for(int i = 0; i < int(s.length()); i++) {
				if(s[i] == ' ') cout << ' ';
				else {
					char k = ((((s[i] - 'A') + off + 26) % 26) + 'A');
					cout << k;
				}
			}
			cout << '\n';
			
			continue;
		} else {
			cout << "NOT POSSIBLE\n";
		}
	}

	return 0;
}