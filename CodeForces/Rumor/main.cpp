#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

typedef unsigned long long int lli;

const int MAX_N = 10e5 + 10;
const lli INF = 99999999999999;

int N, M;
int padre[MAX_N];
int uf_rank[MAX_N];
lli nodes[MAX_N];

int uf_find(int node) {
	if(padre[node] == node)
		return node;
	else {
		int p = uf_find(padre[node]);
		padre[node] = p;
		return p;
	}
}

void uf_union(int na, int nb) {
	int a = uf_find(na);
	int b = uf_find(nb);
	if(a != b) {
		if(uf_rank[b] > uf_rank[a]) {
			padre[b] = a;
			uf_rank[a]++;
		} else {
			padre[a] = b;
			uf_rank[b]++;
		}
	}
}

void uf_init() {
	for(int i = 0; i < N; i++) {
		padre[i] = i;
		uf_rank[i] = 0;
	}
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	cin >> N >> M;
	
	uf_init();
	
	for(int i = 0; i < N; i++) {
		cin >> nodes[i];
	}
	
	for(int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		uf_union(a, b);
	}
	
	vector<lli> mn(N, INF);
	for(int i = 0; i < N; i++) {
		int k = uf_find(i);
		if(nodes[i] < mn[k])
			mn[k] = nodes[i];
	}
	
	lli sum = 0;
	for(int i = 0; i < N; i++) {
		//cout << i << ": V: " << count[i] << endl;
		if(mn[i] != INF)
			sum += mn[i];
	}
	cout << sum << endl;
	
	return 0;
}