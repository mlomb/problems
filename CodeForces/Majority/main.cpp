#include <iostream>
#include <iomanip>
#include <algorithm>
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

	int T;
	cin >> T;
	for(int j = 0; j < T; j++) {
		int V, K;
		cin >> V;
		
		map<int, int> votes;
		
		for(int i = 0; i < V; i++) {
			cin >> K;
			votes[K]++;
		}
		
		pair<int,int> mx;
		for(pair<int,int> p: votes) {
			if(p.second > mx.second) {
				mx = p;
			}
		}
		
		cout << mx.first << endl;
	}
	
	return 0;
}