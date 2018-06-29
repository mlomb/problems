#include <iostream>
#include <fstream>

using namespace std;

const int pattern[3] = { 'V', 'R', 'A' };

int main() {
	ifstream cin("baldosas.in");
#ifndef LOCAL
	ofstream cout("baldosas.out");
#endif

	string s;
	cin >> s;
	
	int offset = 0;
	
	// V, R, A
	for(int i = 0; i < s.length(); i++){
		if(s[i] != '*'){
			int pos;
			switch(s[i]){
				case 'V': pos = 1; break;
				case 'R': pos = 2; break;
				case 'A': pos = 3; break;
			}
			offset = pos - ((i + 1) % 3);
			break;
		}
	}
	
	offset += 3;
	for(int i = 0; i < s.length(); i++)
		s[i] = pattern[(i + offset) % 3];
	
	cout << s << endl;
	
	return 0;
}
