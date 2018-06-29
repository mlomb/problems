#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_B = 10000 + 10;
const int INF = 999999999;

struct Edge {
	int id;
	int source, dist;
	bool closed;
};

struct Node {
	int best[3];
	int pred[3][2];
};

int main(){
	ifstream cin("ciudad.in");
#ifndef LOCAL
	ofstream cout("ciudad.out");
#endif

	int B, G, O;
	cin >> B >> G >> O;

	vector<vector<Edge>> edges;
	edges.resize(B + 1);

	int source, dest, dist;
	for (int i = 0; i < G + O; i++){
		cin >> source >> dest >> dist;
		edges[dest].emplace_back(Edge{ (i - G) + 1, source, dist, i >= G });
	}

	Node nodes[MAX_B];
	nodes[1].best[0] = 0;
	nodes[1].best[1] = INF;
	nodes[1].best[2] = INF;

	for (int i = 2; i <= B; i++){
		Node& node = nodes[i];
		for (int k = 0; k <= 2; k++){
			node.best[k] = INF;
			node.pred[k][0] = 0;
			node.pred[k][1] = 0;
			for (const Edge& e : edges[i]){
				Node& node_source = nodes[e.source];
				
				int w = INF;
				int pred[2] = { 0, 0 };
				
				if(e.closed) {
					if(k == 0) continue;
					else if(k == 1) {
						w = node_source.best[0] + e.dist;
						pred[0] = e.id;
					} else if(k == 2){
						w = node_source.best[1] + e.dist;
						pred[0] = node_source.pred[1][0];
						pred[1] = e.id;
					}
				} else {
					w = node_source.best[k] + e.dist;
					pred[0] = node_source.pred[k][0];
					pred[1] = node_source.pred[k][1];
				}
				
				if (w < node.best[k]){
					node.best[k] = w;
					node.pred[k][0] = pred[0];
					node.pred[k][1] = pred[1];
				}
			}
		}
	}
	
	/*
	for (int k = 0; k <= 2; k++){
		for(int i = 0; i <= B; i++) {
			cout <<	nodes[i].best[k] << "(" <<nodes[i].pred[k][0]<<", " << nodes[i].pred[k][1] << ") ";
		}
		cout << endl;
	}
	*/
	
	Node& last = nodes[B];
	
	if(last.best[2] < last.best[1] && last.best[1] < last.best[0]) {
		cout << "3 " << last.pred[2][0] << " " << last.pred[2][1] << " " << last.best[2] << endl;
	} else if(last.best[1] < last.best[0]){
		cout << "2 " << last.pred[1][0] << " " << last.best[1] << endl;
	} else {
		cout << "1 " << last.best[0];
	}
	
	return 0;
}
