#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

void solve(vector<vector<int>>& dp, vector<vector<bool>>& map, int N, int M){
	for(int i = 1; i < M; i++){
		for(int j = 1; j < N; j++) {
			if(map[i][j])
				dp[i][j] = 0;
			else {
				dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
			}
		}
	}
	
	/*
	cout << endl;
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
	*/
}

void findBest(vector<vector<int>>& dp, int N, int M, int& fil, int& col, int& size) {
	fil = -1;
	col = -1;
	size = 0;
	
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++) {
			if(dp[i][j] > size) {
				size = dp[i][j];
				fil = i - size + 1;
				col = j - size + 1;
			}
		}
	}
}

int main() {
	ifstream fin("yurumi.in");

	int M, N, X;
	fin >> M >> N >> X;
	 
	vector<vector<bool>> map = vector<vector<bool>>(M, vector<bool>(N, false));
	vector<vector<int>> dp = vector<vector<int>>(M, vector<int>(N, -1));
	for(int i = 0; i < M; i++)
		dp[i][0] = 1;
	for(int i = 0; i < N; i++)
		dp[0][i] = 1;
	
	int fil, col;
	for (int i = 0; i < X; i++) {
		fin >> fil >> col;
		fil--;
		col--;
		if(fil < 0 || fil >= M)
			continue;
		if(col < 0 || col >= N)
			continue;
		map[fil][col] = true;
		dp[fil][col] = 0;
	}
	
	int size;
	solve(dp, map, N, M);
	findBest(dp, N, M, fil, col, size);
	
	ofstream fout("yurumi.out");
	fout << fil << " " << col << " " << size << endl;
		
	for(int i = max(fil - 1, 0); i < min(fil + size + 1, M - 1); i++){
		for(int j = max(col - 1, 0); j < min(col + size + 1, N - 1); j++){
			map[i][j] = true;
			dp[i][j] = 0;
		}
	}
	
	solve(dp, map, N, M);
	findBest(dp, N, M, fil, col, size);
	fout << fil << " " << col << " " << size << endl;
	
	return 0;
}
