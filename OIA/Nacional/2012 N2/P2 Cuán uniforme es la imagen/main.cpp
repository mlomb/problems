#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

const int MAX_N = 2000;
const int dirs[4][2] = { {0,1}, {1, 0}, {0,-1}, {-1, 0} };

bool current_painting;
int N;
int map[MAX_N][MAX_N];

struct Point {
	int y, x;
};

int bfs() {
	int result = 0;
	
	current_painting = map[0][0];
	
	queue<Point> q[2];
	
	q[current_painting].push({ 0, 0 });

	while(!q[0].empty() || !q[1].empty()){
		if(q[current_painting].empty()){
			current_painting = !current_painting;
			result++;
			
			/*
			for(int i = 0; i < N; i++){
				for(int j = 0; j < N; j++){
					cout << map[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;
			*/
		}
		const Point& p = q[current_painting].front();
		q[current_painting].pop();
		
		for(int i = 0; i < 4; i++) {
			Point pp = { p.y + dirs[i][1], p.x + dirs[i][0] };
			
			if(pp.x >= 0 && pp.y >= 0 && pp.x < N && pp.y < N) {
				if(map[pp.y][pp.x] != 2){
					q[map[pp.y][pp.x]].push(pp);
					map[pp.y][pp.x] = 2;
				}
			}
		}
	}
	
	return result;
}

int main() {
	ifstream cin("uniformar.in");
	ofstream fout("uniformar.out");
	
	cin >> N;
	
	char c;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cin >> c;
			map[i][j] = c == '1' ? 1 : 0;
		}
	}
	
	fout << bfs() << "\n";
	
	return 0;
}
