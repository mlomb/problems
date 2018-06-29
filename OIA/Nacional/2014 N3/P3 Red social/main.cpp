// Empezado 27/8 23:22
// Terminado 28/8 12:18
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct Node {
	char* name;
	vector<Node*> connections;
	
	int worst;
	int best;
};

void maxDistance(Node* root, int current) {
	if(root->best < current){
		return;
	}
	
	root->best = current;
	
	for(Node* n : root->connections){
		maxDistance(n, current + 1);
	}
}

void resetNodes(vector<Node*>& nodes){
	for(Node* n : nodes){
		n->best = 1 << 30; // infinito
	}
}

Node* findNodeOrCreate(char* name, vector<Node*>& nodes){
	for(Node* n : nodes){
		if(strcmp(n->name, name) == 0){
			return n;
		}
	}
	// Node not found, create
	Node* node = new Node();
	node->name = name;
	nodes.push_back(node);
	return node;
}

int grado(int P, char pares[60000][2][12], int* nl, char lejanos[3000][12]){
	vector<Node*> nodes;
	for(int i = 0; i < P; i++) {
		Node* nodeA = findNodeOrCreate(pares[i][0], nodes);
		Node* nodeB = findNodeOrCreate(pares[i][1], nodes);
		
		nodeA->connections.push_back(nodeB);
		nodeB->connections.push_back(nodeA);
	}
	
	for(Node* root : nodes){
		resetNodes(nodes);
		maxDistance(root, 0);
		
		// Save the worst
		for(Node* n : nodes) {
			if(n->best > n->worst)
				n->worst = n->best;
		}
		
		/*
		// DEBUG
		cout << root->name << " (worst=" << root->worst << "):" << endl;
		for(Node* n : nodes) {
			cout << n->name << "=" << n->best << ", ";
		}
		cout << endl;
		*/
	}
	
	int worst = 0;
	int lejanosI = 0;
	for(Node* n : nodes) {
		if(n->worst > worst){
			worst = n->worst;
			
			// clear lejanos
			lejanosI = 0;
		}
		if(n->worst == worst){
			// add to lejanos
			strncpy(lejanos[lejanosI++], n->name, strlen(n->name));
		}
	}
	*nl = lejanosI + 1;
	
	// sort lejanos
	qsort(lejanos, lejanosI, sizeof(lejanos[0]), [](const void* a, const void* b){
	    const char* aa = (const char*)a;
	    const char* bb = (const char*)b;
	    return strcmp(aa, bb);
	});
	
	return worst;
}

void setName(char* pos, const string name){
	strcpy(pos, name.c_str());
}

int main() {
	int P = 14;
	int nl;
	
	char lejanos[3000][12];
	char pares[60000][2][12];
	
	setName(pares[0][0], "kevin");
	setName(pares[0][1], "gustavo");
	setName(pares[1][0], "daniela");
	setName(pares[1][1], "horacio");
	setName(pares[2][0], "joaquin");
	setName(pares[2][1], "kevin");
	setName(pares[3][0], "clara");
	setName(pares[3][1], "ignacio");
	setName(pares[4][0], "belen");
	setName(pares[4][1], "esteban");
	setName(pares[5][0], "belen");
	setName(pares[5][1], "andrea");
	setName(pares[6][0], "gustavo");
	setName(pares[6][1], "federico");
	setName(pares[7][0], "clara");
	setName(pares[7][1], "belen");
	setName(pares[8][0], "joaquin");
	setName(pares[8][1], "clara");
	setName(pares[9][0], "gustavo");
	setName(pares[9][1], "andrea");
	setName(pares[10][0], "daniela");
	setName(pares[10][1], "belen");
	setName(pares[11][0], "federico");
	setName(pares[11][1], "daniela");
	setName(pares[12][0], "ignacio");
	setName(pares[12][1], "horacio");
	setName(pares[13][0], "belen");
	setName(pares[13][1], "ignacio");
	
	int max = grado(P, pares, &nl, lejanos);
	cout << max << endl;
	
	for(int i = 0; i < nl; i++){
		cout << lejanos[i] << endl;
	}
	return 0;
}
