#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef long long int lli;

const int MAX_N = 100000 + 100;

int depth[MAX_N];
int trace[2*MAX_N-1];
int trace_i;

int first_in_trace[MAX_N];

lli cost[MAX_N];

pair<int, int> st[2*MAX_N*6]; // depth, pos

void DFS(const vector< vector< pair<int, lli> > >& tree, int node, int node_depth, lli node_cost, int parent_node) {
	first_in_trace[node] = trace_i;
	trace[trace_i++] = node;
	depth[node] = node_depth;
	cost[node] = node_cost;
	
	for(auto& cc : tree[node]) {
		if(cc.first == parent_node)
			continue;
		DFS(tree, cc.first, node_depth+1, node_cost + cc.second, node);
		trace[trace_i++] = node;
	}
}


void LCA_build_ST(int left, int right, int pos) {
	if(left == right) {
		st[pos] = make_pair(depth[trace[left]], trace[left]);
		return;
	}
	
	int mid = (left + right) / 2;
	LCA_build_ST(left,      mid, 2 * pos + 1);
	LCA_build_ST(mid + 1, right, 2 * pos + 2);
	
	st[pos] = min(st[2 * pos + 1], st[2 * pos + 2]);
}

pair<int, int> LCA_RMQ(const int qleft, const int qright, int left, int right, int pos) {
	// total overlap
	if(qleft <= left && qright >= right)
		return st[pos];
	
	// no overlap
	if(right < qleft || left > qright)
		return make_pair(99999999, -1);
		
	// partial overlap
	int mid = (left + right) / 2;
	pair<int, int> a = LCA_RMQ(qleft, qright, left,      mid, 2 * pos + 1);
	pair<int, int> b = LCA_RMQ(qleft, qright, mid + 1, right, 2 * pos + 2);
	
	return min(a, b);
}

int LCA(int a, int b) {
	int first = a;
	int second = b;
	
	if(first_in_trace[first] > first_in_trace[second])
		swap(first, second);
	
	return LCA_RMQ(first_in_trace[first], first_in_trace[second], 0, trace_i, 0).second;
}

int main() {
	//ifstream cin("ants.in");
	
	int N;
	cin >> N;
	while(N != 0) {
		vector< vector< pair<int, lli> > > tree(N); // a -> (b, weight) -- bidireccional!
		
		for(int a = 0; a < N - 1; a++) {
			int b, l;
			cin >> b >> l;
			tree[a + 1].push_back(make_pair(b, l));
			tree[b].push_back(make_pair(a + 1, l));
		}
		
		trace_i = 0;
		DFS(tree, 0, 0, 0, -1);
		LCA_build_ST(0, trace_i, 0);
		
		int Q;
		cin >> Q;
		
		for(int i = 0; i < Q; i++) {
			int s, t;
			cin >> s >> t;
			
			int lca = LCA(s, t);
			
			//cout << "S=" << s << ", T=" << t << endl;
			//cout << "lca=" << lca << endl;
			
			lli r = cost[s] + cost[t] - 2*cost[lca];
			if(i)
				cout << " ";
			cout << r;
		}
		cout << endl;
		
		cin >> N;
	}
	
	return 0;
}
