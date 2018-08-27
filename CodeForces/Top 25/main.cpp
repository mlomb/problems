#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <set>
#include <bitset>
#include <functional>
#include <string>
#include <map>

using namespace std;

std::hash<std::string> h_fn;

int hash_str(const string& s) {
	return h_fn(s);
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int T;
	cin >> T;
	
	vector<string> A;
	vector<string> B;
	string s;
	int c = 0; // pendientes
	int d = 0; // pendientes cuenta
	
	for(int i = 0; i < T; i++) {
		int N;
		cin >> N;
		
		A.clear();
		B.clear();
		map<string, int> m; // added count
		
		A.resize(N);
		B.resize(N);
		
		for(int j = 0; j < N; j++) {
			cin >> A[j];
		}
		for(int j = 0; j < N; j++) {
			cin >> B[j];
		}
		
		for(int j = 0; j < N; j++) {	
			m[A[j]]++;
			
			if(m[A[j]] == 2) {
				c--;
				d++;
			} else {
				c++;
			}
			
			m[B[j]]++;
			
			if(m[B[j]] == 2) {
				c--;
				d++;
			} else {
				c++;
			}
			
			if(c == 0 && d > 0) {
				cout << d << " ";
				d = 0;
			}
		}
		
		cout << '\n';
	}
	
	return 0;
}