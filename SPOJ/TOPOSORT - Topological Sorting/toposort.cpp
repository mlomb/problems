#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAX_N = 10000 + 10;

int indegree[MAX_N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
#ifdef LOCAL
	ifstream cin("toposort.in");
#endif
	
	int N, M;
	cin >> N >> M;
	
	vector< vector<int> > edges(N); 
	
	for(int i = 0; i < M; i++){
		int a, b;
		cin >> a >> b;
		a--; b--;
		edges[a].push_back(b);
		
		// "job a needs to be done before job b"
		indegree[b]++;
	}
	
	vector<int> result;
	result.reserve(N);
	
	priority_queue<int, vector<int>, greater<int>> q;
	
	for(int i = 0; i < N; i++){
		if(indegree[i] == 0)
			q.push(i);
	}
	
	while(!q.empty()) {
		int node = q.top();
		q.pop();
		
		result.push_back(node);
		
		for(int cnode : edges[node]) {
			indegree[cnode]--;
			if(indegree[cnode] == 0)
				q.push(cnode);
		}
	}
	
	if(result.size() == N) {
		for(int i = 0; i < result.size(); i++)
			cout << (i ? " " : "") << result[i]+1;
	} else
		cout << "Sandro fails.";
	cout << "\n";
	
	return 0;
}
