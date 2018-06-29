#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int MAX_E = 1000 + 10;
const int MAX_D = 10000 + 10;

int E, D;
int best = 0;
int teams[MAX_E];

void dfs(const vector<vector<int>>& combinations, const int start, const int games) {
	best = max(best, games);
	
	for(int i = start; i < E; i++){
		int a = i + 1;
		
		if(teams[a] > 0) {
			teams[a]--;
			
			for(int b : combinations[a]){
				if(teams[b] > 0){
					teams[b]--;
					
					dfs(combinations, i, games + 1);
					
					teams[b]++;
				}
			}
			
			teams[a]++;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	ifstream fin("balompie.in");
#ifndef LOCAL
	ofstream cout("balompie.out");
#endif
	
	fin >> E >> D;
	
	vector<vector<int>> combinations;
	combinations.resize(MAX_E);
	
	for(int i = 0; i < E; i++)
		fin >> teams[i + 1];
	
	int a, b;
	for(int i = 0; i < D; i++){
		fin >> a >> b;
		if(a > b) swap(a, b);
		combinations[a].push_back(b);
	}
	
	/*
	for(int i = 0; i < E; i++){
		cout << i << " -> ";
		for(int j : combinations[i])
			cout << j << ", ";
		cout << endl;
	}
	*/
	
	dfs(combinations, 0, 0);
	
	cout << best << "\n";
	
	return 0;
}
