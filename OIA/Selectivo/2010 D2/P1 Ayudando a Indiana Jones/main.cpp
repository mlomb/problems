#include <iostream>
#include <fstream>
#include <vector>

#define INF 99999999

using namespace std;

struct Calesita {
	char sentido;
	int minDown = INF, minRight = INF;
};

int main() {
	ifstream fin("indiana.in");
	
	int N;
	fin >> N;
	vector<vector<Calesita>> map(N + 1, vector<Calesita>(N + 1));
	
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			fin >> map[i + 1][j + 1].sentido;
	
	map[1][0].minRight = 0;
	
	for(int i = 1; i < N + 1; i++){
		for(int j = 1; j < N + 1; j++){
			int fromLeft = map[i][j - 1].minRight;
			int fromTop = map[i - 1][j].minDown;
			
			Calesita& c = map[i][j];
			if(c.sentido == 'H'){
				c.minRight = min(fromLeft + 2, fromTop + 1);
				c.minDown = min(fromLeft + 3, fromTop + 2);
			} else {
				c.minRight = min(fromLeft + 2, fromTop + 3);
				c.minDown = min(fromLeft + 1, fromTop + 2);
			}
		}
	}
	
	ofstream fout("indiana.out");
	fout << map[N][N].minRight << endl;
	
	return 0;
}
