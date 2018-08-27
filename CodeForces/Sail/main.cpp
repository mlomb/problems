#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int dist_manh(int x0, int y0, int x1, int y1) {
	return abs(x1 - x0) + abs(y1 - y0);
}
int main() {
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int t, sx, sy, ex, ey;
	string path;
	
	cin >> t >> sx >> sy >> ex >> ey;
	cin >> path;
	
	int time = 0;
	
	for(char c : path) {
		time++;
		int dx = 0;
		int dy = 0;
		
		switch(c) {
			case 'N':
				dx = 0;
				dy = 1;
			break;
			case 'S':
				dx = 0;
				dy = -1;
			break;
			case 'E':
				dx = 1;
				dy = 0;
			break;
			case 'W':
				dx = -1;
				dy = 0;
			break;
		}
		
		int nx = sx + dx;
		int ny = sy + dy;
		
		if(dist_manh(nx, ny, ex, ey) < dist_manh(sx, sy, ex, ey)) {
			sx = nx;
			sy = ny;
		}
		if(sx == ex && sy == ey) {
			cout << time << endl;
			return 0;
		}
	}
	cout << -1 << endl;
	
	return 0;
}