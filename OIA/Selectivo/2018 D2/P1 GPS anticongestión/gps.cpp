#include <vector>
#include <set>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll INF = 999999999999999999;
const int MAX_PATHS = 8000;
const int MAX_SPAWNS = 12000;

struct A {
	ll dist;
	int node;
	
};
bool operator<(const A& l, const A& r) {
	return l.dist > r.dist;
}

vector<vector<pair<int, ll>>> edges; // a -> (b, time)
int spawned[1000 + 10];

vector<ll> spfa(int start, int end) {
	vector<ll> ans;
	ans.reserve(MAX_PATHS);
	
	priority_queue<A> q;
	q.push(A { 0, start });
	
	while(!q.empty()) {
		A node_dist = q.top();
		q.pop();
		
		for(const pair<int, ll>& ve : edges[node_dist.node]) {
			// propagate
			ll dist = node_dist.dist + ve.second;
			if(spawned[ve.first] < MAX_SPAWNS /* int(ans.size()) < MAX_PATHS */) {
				spawned[ve.first]++;
				q.push(A { dist, ve.first });
			}
			if(ve.first == end) {
				ans.push_back(dist);
			}
		}
	}
	
	return ans;
}

vector<long long> gps(int N, int M, int comienzo, int fin, int K, vector<int> origen, vector<int> destino, vector<int> tiempo)
{
	comienzo--;
	fin--;
	
	edges.resize(N);
	for(int i = 0; i < M; i++) {
		int a = origen[i] - 1;
		int b = destino[i] - 1;
		edges[a].push_back(make_pair(b, (ll)tiempo[i]));
	}
	
    vector<ll> ans = spfa(comienzo, fin);
    
	sort(ans.begin(), ans.end());
	ans.resize(K);
    
    return ans;
}
