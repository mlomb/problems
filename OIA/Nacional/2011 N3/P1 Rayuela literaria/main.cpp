#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Node {
	char letter;
	int best = 0;

	vector<Node*> childs;
};

Node* insertTrie(Node* node, string word, int pos = 0) {
	if (pos >= word.size())
		return node;

	char c = word[pos];
	for (Node* n : node->childs)
		if (n->letter == c)
			return insertTrie(n, word, pos + 1);

	Node* n = new Node();
	n->letter = c;
	node->childs.push_back(n);

	return insertTrie(n, word, pos + 1);
}

void solve_sub(int fil, int col, Node* node, int D, char** letters, int** points, int best) {
	if (fil < 0 || col < 0 || fil > D - 1 || col > D - 1)
		return;

	if (node->letter != letters[fil][col])
		return;
	
	best += points[fil][col];
	if (best > node->best)
		node->best = best;

	for (Node* cn : node->childs) {
		solve_sub(fil + 1, col, cn, D, letters, points, best);
		solve_sub(fil - 1, col, cn, D, letters, points, best);
		solve_sub(fil, col + 1, cn, D, letters, points, best);
		solve_sub(fil, col - 1, cn, D, letters, points, best);
	}
}

void solve(Node* root, int D, char** letters, int** points) {
	for (int fil = 0; fil < D; fil++)
		for (int col = 0; col < D; col++)
			for (Node* n : root->childs)
				solve_sub(fil, col, n, D, letters, points, 0);
}

int main() {
	ifstream fin("rayuela_stress.in");
	ios::sync_with_stdio(false);

	int D, P;
	fin >> D >> P;

	char** letters = new char*[D];
	int** points = new int*[D];
	for (int i = 0; i < D; ++i)
		letters[i] = new char[D],
		points[i] = new int[D];

	char c;
	int p;
	for (int fil = 0; fil < D; fil++) {
		for (int col = 0; col < D; col++) {
			fin >> c >> p;
			letters[fil][col] = c;
			points[fil][col] = p;
		} 
	}

	Node* trieRoot = new Node();
	trieRoot->letter = 0;

	vector<Node*> words;

	for (int i = 0; i < P; i++) {
		string word;
		fin >> word;
		words.push_back(insertTrie(trieRoot, word));
	}

	solve(trieRoot, D, letters, points);

	for (const Node* n : words)
		cout << n->best << "\n";

	return 0;
}
