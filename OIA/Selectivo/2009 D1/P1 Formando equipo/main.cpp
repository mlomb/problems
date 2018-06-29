#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

int P, C;
int max_affinity;
string max_affinity_str;

int equalUntil(const string& a, const string& b){
	int equalUntil = 0;
	int sz = min(a.length(), b.length());
	for(; equalUntil < sz; equalUntil++){
		if(a[equalUntil] != b[equalUntil]) break;
	}
	return equalUntil;
}

void cmp(const vector<string>& ss, const int ptrA) {
	int ptrB = ptrA + 1;
	
	int teams = 2;
	int depth = equalUntil(ss[ptrA], ss[ptrB]);
	string match = ss[ptrA].substr(0, depth);
	
	for(;;) {
		ptrB++;
		if(ptrB < C && depth == equalUntil(match, ss[ptrB])){
			teams++;
		} else
			break;
	}
	
	int affinity = depth * depth * teams;
	
	if(affinity > max_affinity) {
		max_affinity = affinity;
		max_affinity_str = match;
	}
}

int main() {
	ifstream cin("equipo.in");
#ifndef LOCAL
	ofstream cout("equipo.out");
#endif

	cin >> P >> C;
	
	vector<string> ss(C);
	
	for (int i = 0; i < C; i++)
		cin >> ss[i];
	
	sort(ss.begin(), ss.end());
	
	//for(string s : ss) cout << s << endl;
	
	for(int i = 0; i < C - 1; i++) cmp(ss, i);
	
	cout << max_affinity << endl;
	cout << max_affinity_str << endl;
	
	return 0;
}
