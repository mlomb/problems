#include <iostream>
#include <vector>
#include <fstream>

// Se puede optimizar mas, por ej con un mapa de bits, pero alta paja.

using namespace std;

struct Queen {
	int x, y;
};

bool solve(int current, int N, vector<Queen>& queens) {
	bool canI;
	int x, y;
	for (int x = 0; x < N; x++) {
		canI = true;
		for (int j = 0; j < current + 1; j++) {
			const Queen& q = queens[j];
			if (x == q.x) {
				canI = false;
				break;
			}
		}
		if (!canI)
			continue;
		
		for (int y = 0; y < N; y++) {
			// Can I put a queen there?
			canI = true;
			for (int j = 0; j < current + 1; j++) {
				const Queen& q = queens[j];
				if (x == q.x || y == q.y || abs(x - q.x) == abs(y - q.y)) {
					canI = false;
					break;
				}
			}
			if (!canI)
				continue;
		
			//cout << current << ": " << y << ", " << x << endl;
	
			Queen& q = queens[current];
			q.x = x;
			q.y = y;
	
			if (current == N - 1) 
				return true;
	
			// Continue solving
			if (solve(current + 1, N, queens))
				return true;
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

	bool solved = solve(M, N, queens);

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
