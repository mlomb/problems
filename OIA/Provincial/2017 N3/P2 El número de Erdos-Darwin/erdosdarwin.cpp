#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>

using namespace std;

struct Node {
	int sums[2] =  { INT_MAX, INT_MAX };
	
	bool visited = false;
	vector<Node*> others;
};

void BFS(Node* root, int sumindex){
	queue<Node*> q;
	q.push(root);
	
	root->sums[sumindex] = 0;
	
	while(!q.empty()){
		Node* n = q.front();
		q.pop();
		
		int spath = n->sums[sumindex] + 1;
		for(Node* cn : n->others){
			if(cn->sums[sumindex] > spath){
				cn->sums[sumindex] = spath;
				cn->visited = false;
			}
			if(!cn->visited) {
				q.push(cn);
				cn->visited = true;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int N, M, d;
	
	cin >> N >> M >> d;
	
	int a, b;
	vector<Node*> nodes = vector<Node*>(N);
	for(int i = 0; i < N; i++)
		nodes[i] = new Node();
	for(int i = 0; i < M; i++) {
		cin >> a >> b;
		a--;
		b--;
		
		nodes[a]->others.push_back(nodes[b]);
		nodes[b]->others.push_back(nodes[a]);
	}
	
	for(Node* n : nodes)
		n->visited = false;
	BFS(nodes[0], 0);
	
	for(Node* n : nodes)
		n->visited = false;
	BFS(nodes[N - 1], 1);
	
	int count = 0;
	for(const Node* n : nodes) {
		if(n->sums[0] == INT_MAX || n->sums[1] == INT_MAX)
			continue;
		if(n->sums[0] + n->sums[1] <= d)
			count++;
	}
	
	cout << count << endl;
	
	return 0;
}