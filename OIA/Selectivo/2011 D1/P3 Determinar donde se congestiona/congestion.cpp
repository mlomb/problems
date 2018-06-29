#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string.h>
#include <cassert>

using namespace std;

typedef long long int lli;

const lli INF = 9999999999;
const int MAX_N = 1000 + 10; // nodes
const int MAX_M = 5000 + 10; // edges

struct Edge {
	int dest;
	lli dist;
	
	int id;
	
	lli sum;
};

int N, M;

// spfa
lli dist[MAX_N]; // distances
int pred[MAX_N]; // predecessor

void spfa(vector<vector<Edge>>& edges, int start){
	queue<int> q;
	
	for(int i = 0; i < N; i++){
		dist[i] = INF;
		pred[i] = -1;
	}
	
	q.push(start);
	dist[start] = 0;
	
	while(!q.empty()){
		int node = q.front();
		q.pop();
		
		for(const Edge& e : edges[node]){
			lli sp = dist[node] + e.dist;
			if(sp < dist[e.dest]) {
				dist[e.dest] = sp;
				pred[e.dest] = node;
				q.push(e.dest);
			}
		}
	}
	
	/*
	cout << " START: " << (start+1) << endl;
	for(int i = 0; i < N; i++){
		cout << (i + 1) << " -- dist: " << dist[i] << ", pred: " << pred[i] << endl;
	}
	*/
	
	// sum up edges
	// worst case N*E
	for(int node = 0; node < N; node++){
		int n = node;
		int p = pred[node];
		while(p != -1){
			//cout << "NODE: " << (node + 1) << ", N:" << (n + 1) << ", P: " << (p + 1) << endl;
			for(Edge& e : edges[p]){
				if(e.dest == n){
					e.sum++;
				}
			}
			
			n = p;
			p = pred[n];
		}
	}
}

int main() {
	ifstream cin("congestion.in");
	ofstream fout("congestion.out");
	
	cin >> N >> M;
	
	vector<vector<Edge>> edges(MAX_N);
	
	int a, b;
	lli d;
	for(int i = 0; i < M; i++) {
		cin >> a >> b >> d;
		a--; b--;
		edges[a].push_back({b, d, i+1, 0});
	}
	
	for(int i = 0; i < N; i++){
		spfa(edges, i);
	}
	
	vector<Edge> result;
	lli m = 0;
	for(int i = 0; i < N; i++){
		for(const Edge& e_other : edges[i]){
			if(e_other.sum > m) {
				m = e_other.sum;
				result.clear();
			}
			if(e_other.sum == m){
				result.push_back(e_other);
			}
		}
	}
	
	fout << result.size() << " " << m << endl;
	for(const Edge& p : result){
		fout << p.id << endl;
	}
	
	return 0;
}