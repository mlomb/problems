#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Casilla {
	int frutales;
	int minSize;
};

const int dir[3][2] {
	{ -1, -1 },
	{ -1,  0 },
	{  0, -1 },
};

int main() {
	ifstream fin("frutales.in");
	int X, Y, P, F;
	fin >> X >> Y >> P >> F;
	
	vector<vector<char>> map = vector<vector<char>>(X, vector<char>(Y, ' '));
	vector<vector<Casilla>> dp = vector<vector<Casilla>>(X, vector<Casilla>(Y, { 0, 1 }));
	
	int fil, col;
	for(int i = 0; i < P; i++){
		fin >> fil >> col;
		fil--;
		col--;
		map[fil][col] = 'P';
		dp[fil][col].minSize = 0;
	}
	for(int i = 0; i < F; i++){
		fin >> fil >> col;
		fil--;
		col--;
		if(fil == 0 || col == 0)
			dp[fil][col].frutales = 1;
		map[fil][col] = 'F';
	}
	
	// DP
	for(int i = 1; i < X; i++){
		for(int j = 1; j < Y; j++){
			if(map[i][j] != 'P') {
				// Busco de las 3 casillas (i-1,j-1 ; i-1,j ; i;j-1)
				// la que tenga el tamaño mas pequeño
				// y despues la que tenga mas frutales
				int mins = 300000;
				int maxf = 0;
				for(int k = 0; k < 3; k++){
					Casilla& other = dp[i + dir[k][0]][j + dir[k][1]];
					
					if(other.minSize == mins){
						maxf = max(maxf, other.frutales);
					} else if(other.minSize < mins){
						mins = other.minSize;
						maxf = other.frutales;
					}
				}
				dp[i][j].minSize = mins + 1;
				dp[i][j].frutales = maxf + (map[i][j] == 'F' ? 1 : 0);
				
			}
		}
	}
	
	for(int i = 0; i < X; i++){
		for(int j = 0; j < Y; j++){
			cout << dp[i][j].frutales << " ";
		}
		cout << endl;
	}
	return 0;
}
