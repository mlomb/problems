#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Queen {
	int x, y;
};

void modifyBoard(int map[], int N, Queen& q, int modifier) {
	for(int i = 0; i < N; i++) {
		// Horizontal
		map[q.x + i * N] += modifier;
		// Vertical
		map[i + q.y * N] += modifier;
		
		// This can also be optimized
		// Diagonal ++
		if(q.x + i < N && q.y + i < N)
			map[(q.x + i) + (q.y + i) * N] += modifier;
		// Diagonal --
		if(q.x - i >= 0 && q.y - i >= 0)
			map[(q.x - i) + (q.y - i) * N] += modifier;
		// Diagonal +-
		if(q.x + i < N && q.y - i >= 0)
			map[(q.x + i) + (q.y - i) * N] += modifier;
		// Diagonal -+
		if(q.x - i >= 0 && q.y + i < N)
			map[(q.x - i) + (q.y + i) * N] += modifier;
	}
	map[q.x + q.y * N] -= 5 * modifier;
}

void printMap(int map[], int N){
	cout << "----" << endl;
	for(int i = 0; i < N * N; i++){
		cout << map[i] << " ";
		if((i + 1) % N == 0)
			cout << endl;
	}
}

int pasos = 0;

bool solve(int current, int N, int map[], vector<Queen>& queens) {
	for (int i = 0; i < N * N; i++) {
		if(map[i] == 0) {
			Queen& q = queens[current];
			q.x = i % N;
			q.y = i / N;
			
			modifyBoard(map, N, q, 1);
			
			pasos++;
			
			//cout << "----" << q.y << ", " << q.x;
			//printMap(map, N);
			
			if (current == N - 1) 
				return true;
			
			// Continue solving
			if (solve(current + 1, N, map, queens))
				return true;
			
			modifyBoard(map, N, q, -1);
			
			//cout << "----" << q.y << ", " << q.x << " GO BACK";
			//printMap(map, N);
		}
	}
	return false;
}

int main() {
	ifstream file("completar.in");
	int N, M;
	file >> N >> M;

	vector<Queen> queens;
	queens.resize(N);
	for (int i = 0; i < M; i++) {
		file >> queens[i].y >> queens[i].x;
		queens[i].x--;
		queens[i].y--;
	}
	
	int* map = new int[N * N];
	for(int i = 0; i < N * N; i++)
		map[i] = 0;
	
	for (int i = 0; i < M; i++) {
		Queen& q = queens[i];
		modifyBoard(map, N, q, 1);
	}
	
	bool solved = solve(M, N, map, queens);

	cout << pasos << endl;
	if (solved) {
		ofstream ofile("completar.out");
		for (int i = M; i < N; i++) {
			Queen& q = queens[i];
			q.x++;
			q.y++;
			ofile << q.y << " " << q.x << endl;
			cout << q.y << " " << q.x << endl;
		}
		ofile.close();
	}
	else {
		cout << "Not solved" << endl;
	}

	return 0;
}
