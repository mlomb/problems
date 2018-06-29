#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	int id;
	bool flag;
	
	vector<Node*> childs = vector<Node*>();
};

vector<Node*> nodes = vector<Node*>();

Node* accquireNode(const int id) {
	for(Node* n : nodes)
		if(n->id == id)
			return n;
	Node* n = new Node();
	n->id = id;
	nodes.push_back(n);
	return n;
}

bool p(Node* searching, const Node* search) {
	if(searching->flag)
		return false;
	searching->flag = true;
	for(Node* n : searching->childs) {
		if(n == search || p(n, search)){
			return true;
		}
		if(find(searching->childs.begin(), searching->childs.end(), n) == searching->childs.end())
			searching->childs.push_back(n);
	}
	return false;
}

int main() {
	ifstream file("conectar.in");
	ofstream fout("conectar.out");
	
	char c;
	int k1, k2;
	while(true) {
		file >> c;
		if(c == 'F')
			break;
		
		file >> k1 >> k2;
		Node* n1 = accquireNode(k1);
		Node* n2 = accquireNode(k2);

		if(c == 'C'){
			n1->childs.push_back(n2);
			n2->childs.push_back(n1);
		} else {
			for(Node* n : nodes)
				n->flag = false;
			fout << (p(n1, n2) ? 'S' : 'N') << "\n";
		}
	}
	
	return 0;
}
