#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>

using namespace std;

const int dir[4][2] {
	{ 0, 1 },
	{ 1, 0 },
	{ -1, 0 },
	{ 0, -1 }
};

int tesoroM, tesoroN;
int M, N, F;

struct Casilla {
	char c;
	int best[125]; // best[flechas] = dist
};
struct Estado {
	int i;
	int j;
	int flechas;
};

void bfs(vector<vector<Casilla>>& map) {
	queue<Estado> q;

  	if(map[0][0].c == 'P')
  		return;
  	
	int f = map[0][0].c == 'W' ? 1 : 0;
  	map[0][0].best[f] = 0;
	q.push({ 0, 0, f });
  
  	if(map[0][0].c == 'T')
  		return;
  		
  		
  	
	int ii, jj, dist, arrows;
	while(!q.empty()){
		Estado& estado = q.front();
		q.pop();
		
		arrows = estado.flechas;
    	dist = map[estado.i][estado.j].best[estado.flechas] + 1;
    	
		if(map[estado.i][estado.j].c == 'W'){
			if(F - arrows < 0)
				continue;
			else
				arrows++;
		}
		
		for(int k = 0; k < 4; k++) {
			ii = estado.i + dir[k][0];
			jj = estado.j + dir[k][1];
			if(ii < 0 || jj < 0 || ii > M -  1 || jj > N - 1)
				continue;
			if(map[ii][jj].c == 'P')
				continue;
			if(map[ii][jj].c == 'W')
				if(estado.flechas == F)
					continue;
			
			int& sd = map[ii][jj].best[arrows];
			if(sd == 1e9 || dist < sd) {
				sd = dist; 
				q.push({ ii, jj, arrows });
			}
		}
	}
}

void reconstructPath(vector<vector<Casilla>>& map, vector<pair<int, int>>& path, const Estado& estado){
	path.emplace_back(make_pair(estado.i, estado.j));
	
	if(estado.i == 0 && estado.j == 0)
		return;

	int currentDist = map[estado.i][estado.j].best[estado.flechas];
  
	for(int k = 0; k < 4; k++){
		int ii = estado.i + dir[k][0];
		int jj = estado.j + dir[k][1];
		if(ii < 0 || jj < 0 || ii > M - 1 || jj > N - 1)
			continue;
		
		int flechas = estado.flechas - (map[ii][jj].c == 'W' ? 1 : 0);
		if(map[ii][jj].best[flechas] == currentDist - 1) {
			reconstructPath(map, path, { ii, jj, flechas });
			return;
		}
	}
}

int main() {
	ifstream fin("tesoro.in");
	ofstream fout("tesoro.out");
	
	fin >> M >> N >> F;
	
	vector<vector<Casilla>> map = vector<vector<Casilla>>(M, vector<Casilla>(N));
	
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			fin >> map[i][j].c;
			if(map[i][j].c == 'T') {
				tesoroM = i;
				tesoroN = j;
			}
			for(int k = 0; k <= 124; k++)
				map[i][j].best[k] = 1e9;
		}
	}
	
	// Resultado
	bfs(map);
	
	// -----
	int minDist = 1e9, flechas;
	for(int k = 0; k <= 124; k++){
		int m = map[tesoroM][tesoroN].best[k];
		if(m < minDist){
			minDist = m;
			flechas = k;
		}
	}
	
	/*
	// DEBUG
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
      		int mm = 1e9;
			for(int k = 0; k < 120; k++)
				mm = min(mm, map[i][j].best[k]);
			if(mm == 1e9)
				cout << "P";
			else
				cout << mm;
			cout << " ";
		}
		cout << endl;
	}
	*/
	
	if(minDist == 1e9){
		fout << "imposible" << endl;
		return 0;
	}
	minDist++;
	fout << minDist << endl;
		
	// Recontruct path
	vector<pair<int, int>> path;
	reconstructPath(map, path, { tesoroM, tesoroN, flechas });
	
	for(auto it = path.rbegin(); it != path.rend(); it++){
		auto kv = (*it);
		fout << "(" << kv.first << "," << kv.second << ")" << endl;
	}
	
	return 0;
}
