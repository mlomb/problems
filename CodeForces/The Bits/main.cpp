#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long int lli;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int N;
	cin >> N;
	
	string a, b;
	cin >> a >> b;
	
	int ones = 0, zeroes = 0;
	int ones_v = 0, zeroes_v = 0;
	for(int i = 0; i < N; i++) {
		if(b[i] == '0') {
			if(a[i] == '0') zeroes_v++;
			else if(a[i] == '1') ones_v++;
		} else {
			if(a[i] == '0') zeroes++;
			else if(a[i] == '1') ones++;
		}
	}
	
	/*
	cout << "ZEROES=" << zeroes << endl;
	cout << "ONES=" << ones << endl;
	*/
	
	lli ways = 0;
	
	for(int i = 0; i < N; i++) {
		if(b[i] == '0') {
			if(a[i] == '0') zeroes_v--;
			else if(a[i] == '1') ones_v--;
			
			if(a[i] == '0') ways += ones + ones_v;
			else if(a[i] == '1') ways += zeroes + zeroes_v;
		}
	}
	
	cout << ways << endl;
	
	return 0;
}