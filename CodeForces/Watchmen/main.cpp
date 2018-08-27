#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <string>
#include <map>
#include <sstream>

using namespace std;

typedef long long int lli;

map<lli, lli> x;
map<lli, lli> y;
map<pair<lli, lli>, lli> rep;

int main() {
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int N;
	cin >> N;
	
	
	
	for(int i = 0; i < N; i++) {
		lli xx, yy;
		cin >> xx >> yy;
		
		x[xx]++;
		y[yy]++;
		rep[make_pair(xx, yy)]++;
	}
	
	lli result = 0;
	
	for(pair<lli, lli> p : x) {
		lli n = p.second;
		result += (n * (n - 1)) / 2;
	}
	for(pair<lli, lli> p : y) {
		lli n = p.second;
		result += (n * (n - 1)) / 2;
	}
	for(pair<pair<lli,lli>, lli> p : rep) {
		lli n = p.second;
		if(n > 1) {
			result -= (n * (n - 1)) / 2;
		}
	}
	
	cout << result << endl;
	
	return 0;
}