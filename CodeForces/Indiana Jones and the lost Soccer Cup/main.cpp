#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
	vector<int> conn;
	int gr_in = 0,
		gr_out = 0;
};
vector<Node> nodes;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int T;
	cin >> T;
	
	for(int t = 0; t < T; t++) {
		int N, M;
		cin >> N >> M;
		
		nodes.clear();
		nodes.resize(N);
		
		int a, b;
		for(int i = 0; i < M; i++) {
			cin >> a >> b;
			a--; b--;
			nodes[a].gr_out++;
			nodes[b].gr_in++;
			nodes[a].conn.push_back(b);
		}
		
		queue<int> q;
		for(int i = 0; i < int(nodes.size()); i++) {
			if(nodes[i].gr_in == 0) {
				q.push(i);
			}
		}
		
		bool multiple_opciones = false;
		int visitados = 0;
		vector<int> path;
		
		while(!q.empty()) {
			int n = q.front();
			q.pop();
			
			visitados++;
			if(q.size() != 0)
				multiple_opciones = true;
			path.push_back(n+1);
			
			for(int h : nodes[n].conn) {
				nodes[h].gr_in--;
				if(nodes[h].gr_in == 0) {
					q.push(h);
				}
			}
		}
		
		if(visitados != N) {
			cout << "recheck hints" << endl;
		} else if(multiple_opciones) {
			cout << "missing hints" << endl;
		} else {
			for(int k : path) {
				cout << k << " ";
			}
			cout << endl;
		}
		
		//cout << visitados << " / " << N << ", " << multiple_opciones << endl;
	}
	
	return 0;
}