#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

const int ALPHABET = 26 + 5;

struct TrieNode {
	TrieNode* parent = 0;
	TrieNode* childs[ALPHABET];
	
	char c;
	int depth = 0;
	int counter = 0;
};

int P, C;

void insertTrie(const string& s, TrieNode* root, vector<TrieNode*>& endNodes){
	TrieNode* lastNode = root;
	
	for(int i = 0; i < P; i++){
		char c = s[i] - 'a';
		TrieNode* node = lastNode->childs[c];
		if(node == 0){
			lastNode->childs[c] = node = new TrieNode();
			node->c = c;
			node->parent = lastNode;
			node->depth = i + 1;
			if(i == P - 1)
				endNodes.push_back(node);
		}
		node->counter++;
		
		lastNode = node;
	}
}

int max_affinity;
TrieNode* max_affinity_node;

void search(const vector<TrieNode*>& nodes){
	vector<TrieNode*> new_nodes;
	
	for(TrieNode* node : nodes){
		int affinity = node->depth * node->depth * node->counter;
		if(affinity > max_affinity){
			max_affinity = affinity;
			max_affinity_node = node;
		}
		
		if(node->parent)
			new_nodes.push_back(node->parent);
	}
	
	if(new_nodes.size() > 0)
		search(new_nodes);
}

void word(string& s, TrieNode* node){
	if(node->parent){
		s.push_back(node->c + 'a');
		word(s, node->parent);
	}
	else
		reverse(s.begin(), s.end());
}

int main() {
	ifstream cin("equipo.in");
#ifndef LOCAL
	ofstream cout("equipo.out");
#endif

	cin >> P >> C;
	
	TrieNode* trie = new TrieNode();
	vector<TrieNode*> endNodes;
	endNodes.reserve(C);
	
	string s;
	for (int i = 0; i < C; i++) {
		cin >> s;
		insertTrie(s, trie, endNodes);
	}
	
	search(endNodes);
	
	string team;
	word(team, max_affinity_node);

	cout << max_affinity << endl;
	cout << team << endl;

	return 0;
}
