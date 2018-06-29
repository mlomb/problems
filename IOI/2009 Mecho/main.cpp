#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string.h>

using namespace std;

typedef long long int lli;

const lli MAX_N = 800 + 10;
const lli INF = 9999999;
const lli dirs[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

struct Point {
	int y, x;
};
struct CellBFS {
	Point p;
	lli time;
};

lli N, S;
Point start;
char map[MAX_N][MAX_N];
bool vis[MAX_N][MAX_N];
lli bees[MAX_N][MAX_N];

bool bfs(lli starting_time){
	//cout << "Starting time: " << starting_time << endl;

	if(starting_time >= bees[start.y][start.x])
		return false;

	memset(vis, false, sizeof(bool) * MAX_N * MAX_N);
	
	queue<CellBFS> q;
	q.push(CellBFS { start, starting_time });
	
	while(!q.empty()){
		CellBFS cbfs = q.front();
		q.pop();
		
		char c = map[cbfs.p.y][cbfs.p.x];
		
		if(c == 'D'){
			//cout << cbfs.time << endl;
			return true;
		}
		
		for(int i = 0; i < 4; i++){
			lli xx = cbfs.p.x + dirs[i][0];
			lli yy = cbfs.p.y + dirs[i][1];
			
			if(xx >= 0 && yy >= 0 && xx < N && yy < N){ // in bounds
				if(!vis[yy][xx]){ // not visited
					vis[yy][xx] = true;
					if(map[yy][xx] == 'G' || map[yy][xx] == 'D'){ // grass or home
						if(cbfs.time < bees[yy][xx]){ // there are not bees in this cell yet
							q.push(CellBFS { { yy, xx }, cbfs.time + 1 });
						}
					}
				}
			}
		}
	}
	
	return false;
}

void expandBeehive(Point p){
	queue<CellBFS> q;
	q.push(CellBFS { p, 0 });
	bees[p.y][p.x] = 0;
	
	while(!q.empty()){
		CellBFS cbfs = q.front();
		q.pop();
		
		for(int i = 0; i < 4; i++){
			lli xx = cbfs.p.x + dirs[i][0];
			lli yy = cbfs.p.y + dirs[i][1];
			
			if(xx >= 0 && yy >= 0 && xx < N && yy < N){ // in bounds
				if(map[yy][xx] == 'G' || map[yy][xx] == 'M'){ // only grass and mecho
					lli time = cbfs.time + S;
					if(time < bees[yy][xx]) { // better
						bees[yy][xx] = time;
						q.push({ { yy, xx }, time });
					}
				}
			}
		}
	}
}

int main(){
#ifdef LOCAL
	ifstream cin("input2.in");
#endif
	
	cin >> N >> S;
	
	vector<Point> beehives;
	
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			char c;
			cin >> c;
			map[i][j] = { c };
			
			if(c == 'M')
				start = { i, j };
			if(c == 'H')
				beehives.push_back({i, j});
		}
	}
	
	// precalc bees
	memset(bees, INF, sizeof(lli) * MAX_N * MAX_N);
	for(Point bee : beehives)
		expandBeehive(bee);
	
	/*
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(bees[i][j] >= INF)
				cout << "X ";
			else
				cout << bees[i][j] << " ";
		}
		cout << endl;
	}
	*/
	
	lli a = -1, b = 2*N*N;
	while(b - a > 1){
		lli time = (a + b) / 2;
		
		if(bfs(time * S))
			a = time;
		else
			b = time;
	}
	
	cout << a << endl;
	
	return 0;
}
