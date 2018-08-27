#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

set<int> sets[200];

struct Query {
	int a, b;
	int intsize;
	//vector<int> s;
};
Query queries[20000 + 10];

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int S;
	cin >> S;
	
	int s1, s2, c;
	int k;
	int r = (S * (S-1)) / 2;
	for(int i = 0; i < r; i++) {
		cin >> s1 >> s2 >> c;
		s1--;
		s2--;
		
		queries[i].a = s1;
		queries[i].b = s2;
		queries[i].intsize = c;
		
		for(int j = 0; j < c; j++) {
			cin >> k;
			sets[s1].insert(k);
			sets[s2].insert(k);
			
			//queries[i].s.push_back(k);
			
		}
		//sort(queries[i].s.begin(), queries[i].s.end());
	}
	
	vector<int> v(30000);
	for(int i = 0; i < r; i++) {
		Query& q = queries[i];
		
		auto end = set_intersection(sets[q.a].begin(), sets[q.a].end(), sets[q.b].begin(), sets[q.b].end(), v.begin());
		
		if(q.intsize/*int(q.s.size())*/ != int(end - v.begin())) {
			cout << "No" << endl;
			return 0;
		}
		
		/*
		int j = 0;
		for(auto it = v.begin(); it  != end; it++, j++) {
			if(*it != q.s[j]) {
				cout << "No" << endl;
				return 0;
			}
		}
		*/
	}
	
	cout << "Yes" << endl;
	for(int i = 0; i < S; i++) {
		cout << sets[i].size() << " ";
		for(int v : sets[i])
			cout << v << " ";
		cout << endl;
	}
	
	
	return 0;
}