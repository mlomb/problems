#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	ifstream cin("mensajes.in");
#ifndef LOCAL
	ofstream cout("mensajes.out");
#endif
	
	int N;
	string s, search;
	
	cin >> N;
	
	for(int i = 0; i < N; i++){
		char c;
		cin >> c;
		s.push_back(c);
	}
	cin >> search;
	
	bool i = s.find(search) != s.npos;
	reverse(s.begin(), s.end());
	bool d = s.find(search) != s.npos;
	
	if(i || d){
		cout << "SI" << endl << (i ? "I" : "D") << endl;
	} else {
		cout << "NO" << endl;
	}
	
	return 0;
}
