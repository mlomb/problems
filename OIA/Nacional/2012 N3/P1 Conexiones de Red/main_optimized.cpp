#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	int id;
	int network;
};

int lastNetwork = 0;
vector<Node> nodes;

int main() {
	ifstream file("conectar.in");
	ofstream fout("conectar.out");
	//nodes.reserve(200000);
	
	char c;
	int k1, k2;
	while(true) {
		file >> c;
		if(c == 'F')
			break;
		
		file >> k1 >> k2;
		
		if(c == 'C'){ // Nueva conexion
			int net1 = -1, net2 = -1;
			for(const Node& n : nodes){
				if(n.id == k1)
					net1 = n.network;
				else if(n.id == k2)
					net2 = n.network;
			}
			int net = lastNetwork++;
			if(net1 == -1)
				nodes.emplace_back(Node{ k1, net });
			if(net2 == -1)
				nodes.emplace_back(Node{ k2, net });
			
			for(Node& n : nodes) {
				if(n.network == net1 || n.network == net2)
					n.network = net;
			}
			
			//for(Node& n : nodes)
			//	cout << n.id << ": " << n.network << endl;
		} else { // Pregunta
			bool result = false;
			int searchN = -1;
			for(const Node& n : nodes){
				if(k1 == n.id || k2 == n.id) {
					if(searchN == -1)
						searchN = n.network;
					else {
						if(n.network == searchN)
							result = true;
						break;
					}
				}
			}
			
			fout << (result ? 'S' : 'N') << "\n";
		}
	}
	
	return 0;
}
