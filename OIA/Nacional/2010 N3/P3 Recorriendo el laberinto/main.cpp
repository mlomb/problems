#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

struct Cell {
	int fil, col;
	int best = 1 << 30;
	bool visited = false;
	
	bool left = false, up = false;
};

void dfs(int fil, int col, int best, Cell** map, int a, int b){
	Cell& cell = map[fil][col];
	if(best < cell.best)
		cell.best = best;
	else
		return;
	
	if(fil + 1 < b && !map[fil + 1][col].up)
		dfs(fil + 1, col, best + 1, map, a, b);
		
	if(col + 1 < a && !map[fil][col + 1].left)
		dfs(fil, col + 1, best + 1, map, a, b);
	
	if(fil - 1 >= 0 && !cell.up)
		dfs(fil - 1, col, best + 1, map, a, b);

	if(col - 1 >= 0 && !cell.left)
		dfs(fil, col - 1, best + 1, map, a, b);
}

int c;
void bfs(Cell** map, int a, int b){
	queue<Cell*> q;
	map[0][0].best = 0;
	q.push(&map[0][0]);
	
	while(!q.empty()){
		Cell* cell = q.front();
		q.pop();
		
		int fil = cell->fil;
		int col = cell->col;
		
		cout << (c++) << endl;
		
		int spath = cell->best + 1;
		
		if(fil + 1 < b && !map[fil + 1][col].up){
			if(spath < map[fil + 1][col].best || !map[fil + 1][col].visited){
				map[fil + 1][col].best = spath;
				q.push(&map[fil + 1][col]);
				map[fil + 1][col].visited = true;
			}
		}
			
		if(col + 1 < a && !map[fil][col + 1].left){
			if(spath < map[fil][col + 1].best || !map[fil][col + 1].visited){
				map[fil][col + 1].best = spath;
				q.push(&map[fil][col + 1]);
				map[fil][col + 1].visited = true;
			}
		}
		
		if(fil - 1 >= 0 && !cell->up){
			if(spath < map[fil - 1][col].best || !map[fil - 1][col].visited){
				map[fil - 1][col].best = spath;
				q.push(&map[fil - 1][col]);
				map[fil - 1][col].visited = true;
			}
		}
	
		if(col - 1 >= 0 && !cell->left){
			if(spath < map[fil][col - 1].best || !map[fil][col - 1].visited){
				map[fil][col - 1].best = spath;
				q.push(&map[fil][col - 1]);
				map[fil][col - 1].visited = true;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	ifstream fin("tabiques.in");
	
	int a, b, t;
	fin >> a >> b >> t;
	
	Cell** map = new Cell*[b];
	for(int i = 0; i < b; i++){
		map[i] = new Cell[a];
		for(int j = 0; j < a; j++){
			map[i][j] = Cell();
			map[i][j].fil = i;
			map[i][j].col = j;
		}
	}
	
	int x1, x2, y1, y2;
	for(int i = 0; i < t; i++){
		fin >> x1 >> y1 >> x2 >> y2;
		bool horizontal = x1 == x2;
		
		for(int fil = y1; fil < y2 + (horizontal ? 0 : 1); fil++){
			for(int col = x1; col < x2 + (horizontal ? 1 : 0); col++){
				if(horizontal)
					map[fil][col].left = true;
				else
					map[fil][col].up = true;
			}
		}
	}
	
	//dfs(0, 0, 0, map, a, b);
	bfs(map, a, b);
	
	/*
	for(int i = b - 1; i >= 0; i--){
		for(int j = 0; j < a; j++){
			cout << map[i][j].left;
		}
		cout << endl;
	}
	*/
	
	ofstream fout("tabiques.out");
	
	if(map[b - 1][a - 1].best == 1 << 30)
		fout << "imposible";
	else
		fout << map[b - 1][a - 1].best;
	fout << "\n";
	
	return 0;
}
