#include <fstream>
#include <cassert>
#include <limits.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>

using namespace std;

const int INF = 99999999;
const int MAX = 200;

int dp[MAX + 1][MAX + 1];

int main() {
	ifstream fin("adn.in");
	ofstream fout("adn.out");
	
	int N, M, K;
	fin >> N >> M >> K;

	string adn_N, adn_M;
	fin >> adn_N >> adn_M;
	
	for(int i = 0; i < MAX; i++) dp[i][0] = i;
	for(int j = 0; j < MAX; j++) dp[0][j] = j;
	dp[0][0] = 0;
	
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			dp[i + 1][j + 1] = min(dp[i][j], min(dp[i + 1][j], dp[i][j + 1])) + (adn_N[i] != adn_M[j]);
		}
	}
	
	for(int i = 0; i < N + 3; i++){
		for(int j = 0; j < M + 3; j++){
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
	
	int mutacionesBest = dp[N][M];

	if (mutacionesBest > K)
		fout << "Muy distintas." << endl;
	else
		fout << mutacionesBest << endl;

	return 0;
}
