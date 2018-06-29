#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

const int MAX_N = 100000 + 10;
const int MAX_M = 300000 + 10;

struct Edge {
	int id;
	int dest, L;
};

int N, M, S;
int max_dist;
vector<Edge> edges[MAX_N];
set<int> not_visited;

bool dfs(int node, vector<int>& solution, int dist) {
	if(dist > max_dist) return false;
	
	if(node == S && not_visited.empty()){
		return true;
	}
	
	for(int i = 1; i >= 0; i--){
		for(const Edge& e : edges[node]){
			if(not_visited.count(e.id) == i){
				solution.push_back(e.id);
				not_visited.erase(e.id);
				
				if(dfs(e.dest, solution, dist + e.L))
					return true;
				
				not_visited.insert(e.id);
				solution.pop_back();
			}
		}
	}
	
	return false;
}

int main() {
#ifdef LOCAL
	ifstream cin("venecia.in");
#endif
	
	cin >> N >> M >> S;
	S--;
	
	for(int i = 0; i < M; i++){
		int a, b, L;
		cin >> a >> b >> L;
		a--; b--;
		edges[a].push_back({ i + 1, b, L });
		edges[b].push_back({ i + 1, a, L });
		not_visited.insert(i + 1);
		
		max_dist += L;
	}
	max_dist *= 2;
	
	vector<int> solution;
	solution.reserve(M*2);
	dfs(S, solution, 0);
	
	cout << solution.size() << "\n";
	for(int i : solution)
		cout << i << " ";
	cout << endl;
	
	return 0;
}
