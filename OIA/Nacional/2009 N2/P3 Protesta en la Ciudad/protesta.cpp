#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

struct Point {
	int y, x;
};
struct Cell {
	bool cortada = false;
	int dist = 99999999;
	Point predecesor;
};

const int MAX_C = 2000;

int C, E;
Point source, dest;
Cell map[MAX_C][MAX_C];

void check(Point p, bool mano, bool vertical, queue<Point>& q, Point pred) {
	if(p.x < 2 || p.x > C || p.y < 1 || p.y > C)
		return;
	
	Cell& cell = map[p.y][p.x];
	
	Point pred_pred = map[pred.y][pred.x].predecesor;
	
	int dist = map[pred.y][pred.x].dist;
	if((vertical && pred_pred.y - pred.y != pred.y - p.y) ||
	  (!vertical && pred_pred.x - pred.x != pred.x - p.x))
		dist++;
	
	if(!cell.cortada && mano && dist < cell.dist){
		cell.predecesor = pred;
		cell.dist = dist;
		
		q.push(p);
	}
}

int bfs(){
	queue<Point> q;
	q.push(source);
	map[source.y][source.x].dist = 0;
	
	while(!q.empty()){
		const Point& p = q.front();
		q.pop();
		
		cout << p.x << ", " << p.y << endl;
		
		bool mano_horizontal_izquierda = ((p.y + 1) / 2) % 2 == 0;
		bool mano_vertical_arriba = (p.x / 2) % 2 == 0;
		
		check({ p.y - 2, p.x },  mano_vertical_arriba, true, q, p);
		check({ p.y + 2, p.x }, !mano_vertical_arriba, true, q, p);
		check({ p.y, p.x - 2 }, !mano_horizontal_izquierda, false, q, p);
		check({ p.y, p.x + 2 },  mano_horizontal_izquierda, false, q, p);
	}
	
	return 0;
}

int main() {
	ifstream cin("protesta.in");
	#ifndef LOCAL
	ofstream cout("protesta.out");
	#endif
	
	cin >> C >> source.x >> source.y >> dest.x >> dest.y >> E;
	
	int x, y;
	for(int i = 0; i < E; i++){
		cin >> x >> y;
		map[y][x].cortada = true;
	}
	
	cout << bfs() << endl;
	
	for(int i = 0; i < C * 2; i++){
		for(int j = 0; j < C * 2; j++){
			if(map[i][j].dist == 99999999)
				cout << "  ";
			else
				cout << map[i][j].dist << " ";
		}
		cout << endl;
	}
	
	return 0;
}
