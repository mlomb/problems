#include <iostream>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <string.h>
 
using namespace std;
 
const int MAX_N = 1000000 + 10;
 
int cow[MAX_N];
int cows_c[MAX_N];
 
int divs[MAX_N];
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
#ifdef LOCAL
	ifstream cin("patheads.in");
#endif
	
	int N;
	cin >> N;
	
	for(int i = 0; i < N; i++) {
		cin >> cow[i];
		cows_c[cow[i]]++;
	}
	
	for(int i = 0; i < MAX_N; i++) {
		int cant = cows_c[i];
		if(cant > 0) {
			for(int k = i; k < MAX_N; k += i)
				divs[k] += cant;
		}
	}
	
	for(int i = 0; i < N; i++) {
		cout << divs[cow[i]]-1 << "\n";
	}
	
	return 0;
}
