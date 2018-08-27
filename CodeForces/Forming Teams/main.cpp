#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_N = 100 + 10;

int N, M;
int padre[MAX_N];
int edges[MAX_N];

int uf_find(int node) {
	if(padre[node] == node)
		return node;
	else
		return uf_find(padre[node]);
}

void uf_union(int na, int nb) {
	int a = uf_find(na);
	int b = uf_find(nb);
	if(a != b) {
		padre[b] = a;
		edges[a] += edges[b];
	}
}

void uf_init() {
	for(int i = 0; i < N; i++) {
		padre[i] = i;
		edges[i] = 0;
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
	
	for(int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		uf_union(a, b);
		edges[uf_find(b)]++;
	}
	
	vector<int> count(N);
	for(int i = 0; i < N; i++) {
		count[uf_find(i)]++;
	}
	
	int c = 0;
	for(int i = 0; i < N; i++) {
		//cout << i << ": V: " << count[i] << " E: " << edges[i] << endl;
		if(count[i] > 1 && edges[i] == count[i]) {
			if(count[i] % 2 != 0) {
				c++;
			}
		}
	}
	
	if((N - c) % 2 != 0)
		c++;
	
	cout << c << endl;

	return 0;
}