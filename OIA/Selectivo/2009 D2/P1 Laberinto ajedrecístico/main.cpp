#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

const int MAX_N = 1000 + 10;
const int INF = 9999999999;
const int caballo[8][2] = {
	{ 1, -2 },
	{ 2, -1 },
	{ 2, 1 },
	{ 1, 2 },
	{ -1, 2 },
	{ -2, 1 },
	{ -2, -1 },
	{ -1, -2 }
};
const int alfil[4][2] = {
	{ 1, 1 },
	{ 1, -1 },
	{ -1, 1 },
	{ -1, -1 }
};
const int torre[4][2] = {
	{ 1, 0 },
	{ 0, 1 },
	{ -1, 0 },
	{ 0, -1 }
};

struct Point {
	int y, x;
};
struct Cell {
	bool blocked = false;
	int jugadas = INF;
	int puntos_en_contra = INF;
};

int N, C;
Cell map[MAX_N][MAX_N];

bool addMove(const Point p, const int cost, const Cell& from, queue<Point>& q) {
	if(p.x >= 0 && p.y >= 0 && p.x < N && p.y < N) {
		Cell& next = map[p.y][p.x];
		
		if(next.blocked)
			return false;
		
		int new_cost = from.puntos_en_contra + cost;
		int new_jugadas = from.jugadas + 1;
		
		if(new_cost > map[N - 1][N - 1].puntos_en_contra) // early break
			return false;
		
		if(new_cost < next.puntos_en_contra ||
			(new_cost == next.puntos_en_contra && new_jugadas < next.jugadas)) {
			next.puntos_en_contra = new_cost;
			next.jugadas = new_jugadas;
			q.push(p);
		}
		return true;
	}
	
	return false;
}

int main() {
	ifstream cin("ajedrez.in");
#ifndef LOCAL
	ofstream cout("ajedrez.out");
#endif
		
	cin >> N >> C;
	
	int x1, y1, x2, y2;
	for(int i = 0; i < C; i++){
		cin >> y1 >> x1 >> y2 >> x2;
		x1--; y1--; x2--; y2--;
		
		if(x1 == x2 || y1 == y2){ // vert or horz
			if(x2 < x1) swap(x1, x2);
			if(y2 < y1) swap(y1, y2);
			
			if(y1 == y2) { // horz
				for(int x = x1; x <= x2; x++)
					map[y1][x].blocked = true;
			} else if(x1 == x2){ // vert
				for(int y = y1; y <= y2; y++)
					map[y][x1].blocked = true;
			}
		} else { // diagonal
			int dg = abs(max(x2 - x1, y2 - y1));
			
			int dx = x2 - x1 > 0 ? 1 : -1;
			int dy = y2 - y1 > 0 ? 1 : -1;
			
			//cout << "Diagonal: " << (x1 + 1) << ", " << (y1 + 1) << "    " << (x2 + 1) << ", " << (y2 + 1) << "   dx: " << dx << ", dy: " << dy << ",  d: " << dg << endl;
			
			for(int d = 0; d <= dg; d++)
				map[y1 + d * dy][x1 + d * dx].blocked = true;
		}
		
	}
	
	/*
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++) {
			cout << map[i][j].blocked;
		}
		cout << endl;
	}
	*/
	
	queue<Point> q;
	q.push({ 0, 0 });
	map[0][0].jugadas = 0;
	map[0][0].puntos_en_contra = 0;
	
	while(!q.empty()) {
		const Point p = q.front();
		q.pop();
		
		Cell& cell = map[p.y][p.x];
		
		for(int i = 0; i < 8; i++) { // caballos
			addMove({ p.y + caballo[i][1], p.x + caballo[i][0]}, 1, cell, q);
		}

		// alfiles
		for(int i = 0; i < 4; i++) {
			for (int k = 1; k < N + 10; k++) {
				if(!addMove({ p.y + alfil[i][1] * k, p.x + alfil[i][0] * k}, 2, cell, q))
					break;
			}
		}
		
		// torres
		for(int i = 0; i < 4; i++) {
			for(int k = 1; k < N + 10; k++) {
				if(!addMove({ p.y + torre[i][1] * k, p.x + torre[i][0] * k}, 3, cell, q))
					break;
			}
		}
	}
	
	/*
	cout << endl;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++) {
			if (map[i][j].puntos_en_contra == INF)
				cout << "X ";
			else
				cout << map[i][j].puntos_en_contra << " ";
		}
		cout << endl;
	}
	*/
	
	Cell& finish = map[N - 1][N - 1];
	cout << finish.jugadas << " " << finish.puntos_en_contra << "\n";
	
	return 0;
}
