#include <iostream>
#include <vector>
#include <fstream>
 
using namespace std;
 
const int MAX_N = 1000 + 100;
 
int depth[MAX_N];
int trace[2*MAX_N-1];
int trace_i;
 
int first_in_trace[MAX_N];
 
void DFS(const vector< vector<int> >& tree, int node, int node_depth) {
	first_in_trace[node] = trace_i;
	trace[trace_i++] = node;
	depth[node] = node_depth;
	
	for(int child : tree[node]) {
		DFS(tree, child, node_depth+1);
		trace[trace_i++] = node;
	}
}
 
int LCA(int a, int b) {
	/*
	for(int i = 0; i < trace_i + 5; i++) {
		cout << trace[i] << " ";
	}
	cout << endl;
	
	cout << a << " to " << b << endl;
	*/
	
	int first = a;
	int second = b;
	
	if(first_in_trace[first] > first_in_trace[second])
		swap(first, second);
	
	int i = first_in_trace[first];
	int lca = -1, lca_depth = 99999999;
	
	do {
		if(depth[trace[i]] < lca_depth) {
			lca = trace[i];
			lca_depth = depth[lca];
		}
		i++;
	} while(trace[i-1] != second);
	
	//cout << "LCA: " << lca << ", DEPTH: " << lca_depth << endl;
	
	return lca;
}
 
int main() {
	//ifstream cin("lca.in");
	
	int T;
	cin >> T;
	
	for(int i = 0; i < T; i++) {
		int N;
		cin >> N;
		
		vector< vector<int> > tree(N);
		for(int j = 0; j < N; j++) {
			int C;
			cin >> C;
			for(int k = 0; k < C; k++) {
				int child;
				cin >> child;
				child--;
				tree[j].push_back(child);
			}
		}
		
		trace_i = 0;
		DFS(tree, 0, 0);
		
		int Q;
		cin >> Q;
		
		cout << "Case " << i+1 << ":" << endl;
		
		for(int j = 0; j < Q; j++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			cout << LCA(a, b)+1 << endl;
		}
	}
	
	return 0;
}