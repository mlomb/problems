#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int px, py;
int winTarget;
bool placed = false;
int count = 0;
int wx, wy;
vector< vector<char> > map;

void process(int x, int y){
	if(map[x][y] == 'x'){
		placed = false;
		count = 0;
	} else if(map[x][y] == 'o'){
		count++;
	} else {
		px = x;
		py = y;
		if(!placed) count++;
		placed = true;
	}
	
	if(count >= winTarget && px < wx || (px == wx && py < wy)){
		wx = px;
		wy = py;
	}
}

int main(){
	ifstream file("EJ1.txt");
	
	int W, H;
	
	file >> winTarget >> H >> W;
	wx = W + 1;
	wy = H + 1;
	
	map = vector< vector<char> >(W);
	for(int x = 0; x < W; ++x)
		map[x] = vector<char>(H);
	for(int y = 0; y < H; ++y)
		for(int x = 0; x < W; ++x)
			file >> map[x][y];
	
	/* Process */
	// Horizontal
	for(int y = 0; y < H; ++y){
		placed = false;
		count = 0;
		for(int x = 0; x < W; ++x){
			process(x, y);
		}
	}
	// Vertical
	for(int x = 0; x < W; ++x){
		placed = false;
		count = 0;
		for(int y = 0; y < H; ++y){
			process(x, y);
		}
	}
	// Diagonal
	for(int y = 0; y < H; ++y){
		placed = false;
		count = 0;
		for(int xy = 0; xy < H; ++xy){
			if(xy >= W || y + xy >= H)
				break;
				//cout << xy << ", " << y + xy << endl;
			process(xy, y + xy);
		}
	}
	
	if(wx == W + 1)
		cout << -1 << endl;
	else
		cout << wy + 1 << " " << wx + 1 << endl;
	
	return 0;
}
