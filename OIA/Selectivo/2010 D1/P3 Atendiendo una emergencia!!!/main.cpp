#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

typedef long long int lli;

const lli INF = 9999999999;

vector<lli> spfa(const vector<vector<pair<int, lli>>>& neighbors, const int start, const int end) {
	const int nodes = neighbors.size();
	
	vector<lli> dist(nodes, INF);
	queue<int> q;
	
	// gather min distances
	q.push(start);
	dist[start] = 0;
	
	while(!q.empty()){
		int node = q.front();
		q.pop();
		
		for(const pair<int, lli>& n : neighbors[node]){
			int spath = dist[node] + n.second;
			if(spath < dist[n.first]){
				dist[n.first] = spath;
				q.push(n.first);
			}
		}
	}
	
	/*
	for(int i = 0; i < nodes; i++)
		cout << dist[i] << endl;
	cout << endl << endl;
	*/
	
	return dist;
}

int dp[15000 + 1];

lli paths(const vector<vector<int>>& neighbors, int node){
	if(dp[node] != 0)
		return dp[node];

	int sum = 0;

	for(const int dest : neighbors[node]){
		sum += paths(neighbors, dest);
	}
	
	dp[node] = sum;
	
	return sum;
}

int main() {
	ifstream fin("ambulancia.in");
	
	int P, T, S, E;
	fin >> P >> T >> S >> E;
	S--;
	E--;
	
	// dest, dist
	vector<vector<pair<int, lli>>> neighbors(P);
	
	int a, b;
	lli c;
	for(int i = 0; i < T; i++){
		fin >> a >> b >> c;
		a--;
		b--;
		neighbors[a].push_back(make_pair(b, c));
		neighbors[b].push_back(make_pair(a, c));
	}
	
	lli result;
	
	if(S == E)
		result = 0;
	else {
		vector<lli> distS = spfa(neighbors, S, E);
		vector<lli> distE = spfa(neighbors, E, S);
		
		// dest
		vector<vector<int>> neighbors_filtered(P);
		
		// filtramos los edges que para ambos lados nos acercan a S y a E
		for(int source = 0; source < P; source++){
			auto& v = neighbors[source];
			for(auto it = v.begin(); it != v.end(); it++){
				const pair<int, lli>& edge = *it;
				
				int dest = edge.first;
				int d = edge.second;
				
				if(distS[dest] > distS[source] &&
				   distE[source] > distE[dest]){
					neighbors_filtered[dest].push_back(source);
					//cout << (source + 1) << " -> " << (dest + 1) << endl;
				}
			}
		}
		
		dp[S] = 1;
		result = paths(neighbors_filtered, E);
	}
	
	ofstream fout("ambulancia.out");
	fout << result << endl;
	
	return 0;
}
