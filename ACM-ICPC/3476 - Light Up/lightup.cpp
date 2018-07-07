#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

const int INF = 99999999;

int min_lamps = INF;

struct Configuration {
	int N, M;
	int lamps = 0;
	
	int non_lit_cells = 0;
	int barrier_count_cells = 0;
	
	struct Cell {
		int barrier_count;
		bool barrier = false;
		bool lamp = false;
		bool lit = false;
	} board[7][7];
	
	void print() {
		cout << endl;
		for(int r = 0; r < N; r++) {
			for(int c = 0; c < M; c++) {
				if(board[r][c].barrier) {
					if(board[r][c].barrier_count >= 0)
						cout << board[r][c].barrier_count;
					else
						cout << 'X';
				}
				else if(board[r][c].lamp)
					cout << 'L';
				else if(board[r][c].lit)
					cout << ' ';
				else
					cout << '_';
			}
			cout << endl;
		}
	}
	
	bool inBounds(int r, int c){
		return r >= 0 && c >= 0 && r < N && c < M;
	}
	
	void add_lamp_dir(int r, int c, int dx, int dy) {
		if(inBounds(r + dx, c + dy)) {
			if(board[r + dx][c + dy].barrier) {
				if(board[r + dx][c + dy].barrier_count > 0) {
					board[r + dx][c + dy].barrier_count--;
					barrier_count_cells--;
				}
			}
		}
		
		while(inBounds(r, c)) {
			if(board[r][c].barrier)
				return;
			if(!board[r][c].lit){
				board[r][c].lit = true;
				non_lit_cells--;
			}
			r += dx;
			c += dy;
		}
	}
	
	void add_lamp(int r, int c) {
		lamps++;
		board[r][c].lamp = true;
		add_lamp_dir(r, c,  1,  0);
		add_lamp_dir(r, c, -1,  0);
		add_lamp_dir(r, c,  0,  1);
		add_lamp_dir(r, c,  0, -1);
	}
	
	bool isWin() {
		return non_lit_cells == 0 && barrier_count_cells == 0;
	}
	
	bool can_place_lamp_barrier(int r, int c){
		if(!inBounds(r, c))
			return true;
		
		if(board[r][c].barrier) {
			if(board[r][c].barrier_count < 0)
				return true;
			return board[r][c].barrier_count - 1 >= 0;
		}
		
		return true;
	}
	
	bool can_place_lamp(int r, int c) {
		Cell& cell = board[r][c];
		if(!cell.barrier && !cell.lit) {
			return can_place_lamp_barrier(r + 1, c) &&
				   can_place_lamp_barrier(r - 1, c) &&
				   can_place_lamp_barrier(r, c + 1) &&
				   can_place_lamp_barrier(r, c - 1);
		}
		return false;
	}
};

void next(Configuration config) {
	//config.print();
	
	if(config.isWin()) {
		if(config.lamps < min_lamps)
			config.print();
		min_lamps = min(min_lamps, config.lamps);
		return;
	}
	
	if(config.lamps >= min_lamps)
		return;
	
	for(int r = 0; r < config.N; r++) {
		for(int c = 0; c < config.M; c++) {
			if(config.can_place_lamp(r, c)) {
				Configuration new_config = config;
				new_config.add_lamp(r, c);
				next(new_config);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
#ifdef LOCAL
	ifstream cin("lightup.in");
#endif
	
	int N, M, B;
	cin >> N >> M;
	
	while(N != 0 && M != 0) {
		cin >> B;
		
		min_lamps = INF;
		
		Configuration c;
		c.N = N;
		c.M = M;
		c.non_lit_cells = N * M;
		
		for(int i = 0; i < B; i++) {
			int R, C, K;
			cin >> R >> C >> K;
			R--; C--;
			c.board[R][C].barrier = true;
			c.board[R][C].barrier_count = K;
			
			c.non_lit_cells--;
			if(K > 0)
				c.barrier_count_cells += K;
		}
		
		next(c);
		
		if(min_lamps == INF)
			cout << "No solution" << endl;
		else
			cout << min_lamps << endl;
		
		cin >> N >> M;
	}
	
	return 0;
}
