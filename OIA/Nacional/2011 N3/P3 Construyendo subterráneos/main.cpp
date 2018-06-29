#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long int lli;

const lli INF = 1000000000000000;
int N, K;

struct MSTEdge {
	int source, dest;
	lli distance;
	lli distance_from_root;
	lli distance_from_childs;
};

bool childDistSort(const MSTEdge& a, const MSTEdge& b) {
	return a.distance_from_childs > b.distance_from_childs;
}

lli generateMSTEdges(int index, int previous, lli distance_from_root, vector<MSTEdge>& mst_edges, const vector<vector<pair<int, lli>>>& edges) {
	lli max_childs = 0;
	for(pair<int, lli> p : edges[index]){
		if(p.first == previous) continue;

		lli childs = generateMSTEdges(p.first, index, distance_from_root + p.second, mst_edges, edges);
		
		max_childs = max(childs, childs + p.second);
		mst_edges.push_back({ index, p.first, p.second, distance_from_root + p.second, childs + p.second });
	}
	
	return max_childs;
}

void bfs(int from, vector<lli>& dists, const vector<vector<pair<int, lli>>>& edges) {
	dists.resize(edges.size());
	
	queue<int> q;
	q.push(from);
	
	for(lli& i : dists)
		i = INF;
	dists[from] = 0;
	
	while(!q.empty()){
		int node = q.front();
		q.pop();
		
		for(pair<int, lli> p : edges[node]){
			lli dist = dists[node] + p.second;
			if(dist < dists[p.first]) {
				dists[p.first] = dist;
				q.push(p.first);
			}
		}
	}
}

int findCenterNode(const vector<vector<pair<int, lli>>>& edges){
	vector<lli> dists1, dists2;
	
	bfs(0, dists1, edges);
	int furthest1 = max_element(dists1.begin(), dists1.end()) - dists1.begin();
	
	bfs(furthest1, dists2, edges);
	int furthest2 = max_element(dists2.begin(), dists2.end()) - dists2.begin();

	bfs(furthest2, dists1, edges);
	
	int center = 0;
	lli min_diff = INF;
	lli diameter = dists2[furthest2];
	for(int i = 0; i < N; i++){
		if(dists1[i] + dists2[i] == diameter) {
			lli d = abs(dists1[i] - dists2[i]);
			if(d <= min_diff){
				center = i;
				min_diff = d;
			}
		}
	}
	
	return center;
}

lli calc(int center, bool sub, const vector<vector<pair<int, lli>>>& edges){
	vector<MSTEdge> mst_edges;
	mst_edges.reserve(N - 1);
	generateMSTEdges(center, -1, 0, mst_edges, edges);
	
	sort(mst_edges.begin(), mst_edges.end(), childDistSort);
	
	/*
	for(MSTEdge& e : mst_edges){
		cout << (e.source + 1) << " -> " << (e.dest + 1) << " dist_from_root: " << e.distance_from_root << " dist_from_childs: " << e.distance_from_childs << endl;
	}
	*/
	
	lli answer = 0;
	int nodes_used = 0;
	
	lli K_used = 0;
	for(MSTEdge& e : mst_edges){
		K_used += e.distance;
		if(K_used > K) {
			answer = e.distance_from_childs;
			break;
		}
		nodes_used++;
	}
	
	if(nodes_used == 0){
		if(sub) return -1;
		for(MSTEdge& e : mst_edges){
			answer = calc(e.source, true, edges);
			if(answer != -1)
				break;
		}
	}
	
	return answer;
}

int main() {
	ifstream cin("subte.in");
#ifndef LOCAL
	ofstream cout("subte.out");
#endif
	
	cin >> N >> K;
	
	if(K == 0){
		cout << 0 << endl;
		return 0;
	}
	
	vector<vector<pair<int, lli>>> edges(N); // source, dest, L
	
	int a, b;
	lli L;
	for(int i = 0; i < N - 1; i++){
		cin >> a >> b >> L;
		a--; b--;
		edges[a].push_back(make_pair(b, L));
		edges[b].push_back(make_pair(a, L));
	}
	
	int center = findCenterNode(edges);
	
	lli answer = calc(center, false, edges);

	cout << answer << endl;
	
	return 0;
}
