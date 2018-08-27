#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <string>
#include <sstream>

using namespace std;

typedef long long int lli;

const int MAX_N = 1000 + 10;
const lli INF = 9999999999;

struct Cell {
	lli num;
	lli tried[2];
	char from[2];
};

int N;
Cell grid[MAX_N][MAX_N];

lli fact(lli num, lli f) {
	if(num == 0)
		return INF;
	lli res = 0;
	while(num % f ==0) {
		res++;
		num /= f;
	}
	return res;
}

void runDP(int index, lli f) {
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			if(i == 0 && j == 0) continue;
			
			if(grid[i][j].num == 0) {
				grid[i][j].tried[index] = INF;
				continue;
			}
			
			lli from_left = INF,
				from_top = INF;
			
			if(i) {
				from_left = grid[i - 1][j].tried[index];
			}
			if(j) {
				from_top = grid[i][j - 1].tried[index];
			}
			
			grid[i][j].tried[index] = fact(grid[i][j].num, f);
			
			if(from_left < from_top) {
				grid[i][j].tried[index] += grid[i - 1][j].tried[index];
				grid[i][j].from[index] = 'D';
			} else {
				grid[i][j].tried[index] += grid[i][j - 1].tried[index];
				grid[i][j].from[index] = 'R';
			}
		}
	}
}

void reconstruct(int index) {
	int i = N-1,
		j = N-1;
	
	string path;
	
	while(i > 0 || j > 0) {
		char d = grid[i][j].from[index];
		if(d == 'R') {
			j--;
		} else {
			i--;
		}
		path.push_back(d);
	}
	
	reverse(path.begin(), path.end());
	
	cout << grid[N-1][N-1].tried[index] << endl;
	cout << path << endl;
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	cin >> N;
	
	int zy = -1;
	
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			cin >> grid[i][j].num;
			if(grid[i][j].num == 0) {
				zy = j;
			}
		}
	}
	
	grid[0][0].tried[0] = fact(grid[0][0].num, 2);
	grid[0][0].tried[1] = fact(grid[0][0].num, 5);
	
	runDP(0, 2);
	runDP(1, 5);
	
	lli best = min(grid[N-1][N-1].tried[0], grid[N-1][N-1].tried[1]);
	
	if(best >= 1 && zy != -1) {
		cout << "1" << endl;
		for(int i = 0; i < zy; i++)
			cout << 'R';
		for(int i = 0; i < N - 1; i++)
			cout << 'D';
		for(int i = 0; i < (N - zy - 1); i++)
			cout << 'R';
		cout << endl;
		return 0;
	}
	
	if(grid[N-1][N-1].tried[0] < grid[N-1][N-1].tried[1]) {
		// con 2
		reconstruct(0);
	} else {
		// con 5
		reconstruct(1);
	}
	
	/*
	cout << grid[N-1][N-1].tried[0] << ", " << grid[N-1][N-1].tried[1] << endl;
	
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			cout << grid[i][j].tried[0] << " ";
		}
		cout << endl;
	}
	
		cout << endl;
		cout << endl;
		cout << endl;
	
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			cout << grid[i][j].tried[1] << " ";
		}
		cout << endl;
	}
	*/
	
	return 0;
}