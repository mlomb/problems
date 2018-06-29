#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <queue>
#include <string.h>

using namespace std;

const int INF = 999999999;
const int MAX_N = 2000 + 10;
const int alternos[3][2] = { { 1, 2 }, { 0, 2 }, { 0, 1 } };
const int dirs[4][2]     = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

struct Cell {
	int col; // RAV = 0, 1, 2
	bool visited;
};
struct Point {
	int y, x;
};

struct Estado {
	queue<Point> q[3];
	vector<int> colores;
};

int N;
Cell map[MAX_N][MAX_N];

// static result
int best;
vector<int> best_path;

char color_code(int col){
	switch(col){
		case 0: return 'R';
		case 1: return 'A';
		case 2: return 'V';
	}
}

void paint(int color, Estado e){
	int color_from;
	if(e.colores.size() == 0)
		color_from = map[0][0].col;
	else
		color_from = e.colores[e.colores.size() - 1];
	
	e.colores.push_back(color);
	
	if(e.colores.size() >= best) {
		//cout << "Early break" << endl;
		return;
	}
	
	//cout << "--------- " << e.colores.size() << "          " << color_code(color_from) << " -> "<< color_code(color) << "   R " << e.q[0].size() << "  A "<< e.q[1].size() << "  V "<< e.q[2].size() << " "  << endl;
	
	if(e.q[color_from].empty() && e.q[color].empty()) return;
	
	vector<Point> visited;
	
	int expanding = color_from;
	while(!e.q[expanding].empty()){
		Point p = e.q[expanding].front();
		e.q[expanding].pop();
		
		//cout << p.x << ", " << p.y << endl;
		
		for(int i = 0; i < 4; i++){
			Point pp = { p.y + dirs[i][1], p.x + dirs[i][0] };
			
			if(pp.x >= 0 && pp.y >= 0 && pp.x < N && pp.y < N){
				Cell& cell = map[pp.y][pp.x];
			
				if(!cell.visited){
					//cout << "  "<< pp.x << ", " << pp.y << " vis: "  << cell.visited << " col: " << color_code(cell.col) << endl;
				
					cell.visited = true;
					e.q[cell.col].push(pp);
					visited.push_back(pp);
				}
			}
		}
		
		if(expanding == color_from && e.q[expanding].empty())
			expanding = color;
	}
	
	if(e.q[0].empty() && e.q[1].empty() && e.q[2].empty()){
		best = e.colores.size();
		best_path = e.colores;
		
		//cout << "New best: " << best << endl;
	} else {
		if(e.q[alternos[color][0]].size() >= e.q[alternos[color][1]].size()){ // heuristica basica
			paint(alternos[color][0], e);
			paint(alternos[color][1], e);
		} else {
			paint(alternos[color][1], e);
			paint(alternos[color][0], e);
		}
	}
	
	for(Point p : visited)
		map[p.y][p.x].visited = false;
}

int main() {
	ifstream cin("repintar.in");
	ofstream fout("repintar.out");
	
	cin >> N;
	
	char c;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cin >> c;
			map[i][j].col = c == 'R' ? 0 : (c == 'A' ? 1 : 2);
			map[i][j].visited = false;
		}
	}
	
	best = INF;
	
	Estado e;
	map[0][0].visited = true;
	e.q[map[0][0].col].push({ 0, 0 });
	
	paint(alternos[map[0][0].col][0], e);
	paint(alternos[map[0][0].col][1], e);
	
	fout << best << "\n";
	for(int col : best_path)
		fout << color_code(col);
	fout << "\n";
	
	return 0;
}
