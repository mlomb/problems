#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <math.h>

using namespace std;

typedef long long int lli;

const int MAX_N = 1000 + 10;

int network[MAX_N];
int network_rank[MAX_N];

struct Farol {
	int n;
	lli x, y;
};
struct Edge {
	int a, b;
	lli w;
};

bool wSort(const Edge& a, const Edge& b){
	return a.w < b.w;
}

int getRoot(int index){
	if(network[index] == index)
		return index;
	
	return getRoot(network[index]);
}

void pathCompression(int index, const int set_root) {
	if(network[index] == set_root)
		return;
	
	int next = network[index];
	network[index] = set_root;
	
	pathCompression(next, set_root);
}

int main() {
	cin.tie();
	ios::sync_with_stdio(false);
	
	ifstream cin("parque.in");
#ifndef LOCAL
	ofstream cout("parque.out");
#endif

	int N;
	cin >> N;
	
	for(int i = 0; i < N + 1; i++)
		network[i] = i;
	
	vector<Farol> faroles(N + 1);
	faroles[0] = { 0, 0, 0 };
	for(int i = 1; i <= N; i++)
		cin >> faroles[i].n >> faroles[i].x >> faroles[i].y;
	
	
	vector<Edge> edges;
	edges.reserve(N * N);
	for(int i = 0; i < faroles.size(); i++){
		for(int j = i + 1; j < faroles.size(); j++){
			lli dx = abs(faroles[i].x - faroles[j].x);
			lli dy = abs(faroles[i].y - faroles[j].y);
			long double xy = dx * dx + dy * dy;
			lli w = floor(sqrt(xy) + 2);
			
			edges.push_back({ faroles[i].n, faroles[j].n, w });
		}
	}
	
	sort(edges.begin(), edges.end(), wSort);
	
	lli cost = 0;
	set<int> direct[MAX_N];

	for(const Edge& e : edges) {
		int ra = getRoot(e.a);
		int rb = getRoot(e.b);
		
		if(ra != rb) {
			if(network_rank[e.a] < network_rank[e.b])
				pathCompression(e.a, rb);
			else
				pathCompression(e.b, ra);
			
			network_rank[e.a] = network_rank[e.b] = max(network_rank[e.a], network_rank[e.b]) + 1;
			
			direct[e.a].insert(e.b);
			direct[e.b].insert(e.a);
			cost += e.w;
		}
	}
	
	cout << cost << "\n";
	
	for(int i = 1; i <= N; i++){
		cout << i << " ";
		for(int j : direct[i])
			cout << j << " ";
		cout << "\n";
	}
	
	return 0;
}
