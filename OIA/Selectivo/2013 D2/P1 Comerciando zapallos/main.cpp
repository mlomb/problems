#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

struct Estado {
	int ganancia;
	int cajas;
	
	int real_ganancia;	// not nice!
};

int main() {
	ifstream fin("zapallos.in");
	ofstream fout("zapallos.out");
	
	int A, M;
	fin >> A >> M;
	
	Estado** dp = new Estado*[1005];
	for(int i = 0; i < 1005; i++){
		dp[i] = new Estado[1205];
		for(int j = 0; j < 1205; j++){
			dp[i][j] = {0,0,0};
		}
	}
	
	int bestI, bestJ;
	
	int K, C;
	for(int i = 0; i < A; i++){
		fin >> K;
		
		int lastGanancia = 0;
		for(int j = 0; j < K; j++){
			fin >> C;
			lastGanancia += 10 - C;
			
			int maxG = 0, minC = 0;
			if(i > 0){
				for(int m = 0; m < min(K, M - j); m++){
					Estado& e = dp[i - 1][m];
					if(e.ganancia > maxG || (e.ganancia == maxG && e.cajas < minC)) {
						if(e.cajas + j + 1 <= M){
							maxG = e.ganancia;
							minC = e.cajas;
						}
					}
				}
			}
			
			//cout << i << ", " << j << ", " << lastGanancia << " || " << maxG << ", " << minC << endl;
			if(lastGanancia > 0){
				maxG += lastGanancia;
				minC += j + 1;
			}
			dp[i][j].real_ganancia = lastGanancia;
			dp[i][j].ganancia = maxG;
			dp[i][j].cajas = minC;
			
			Estado& bestE = dp[bestI][bestJ];
			if(maxG > bestE.ganancia || (maxG == bestE.ganancia && minC < bestE.cajas)){
				bestI = i;
				bestJ = j;
			}
		}
	}
	
	/*
	// DEBUG
	for(int i = 0; i < A; i++){
		for(int j = 0; j < 12; j++){
			cout << dp[i][j].ganancia << "(" << dp[i][j].cajas << ")" << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
	*/
	
	Estado& bestE = dp[bestI][bestJ];
	fout << bestE.ganancia << " " << bestE.cajas << endl;
	
	int cajas[1005];
	int lastMaxGanancia = bestE.ganancia;
	for(int i = bestI; i >= 0; i--){
		for(int j = 0; j < 100; j++){
			//cout << i << ", " << j << " || " << lastMaxGanancia <<" - " << dp[i][j].real_ganancia << " == " << dp[i][j].ganancia << endl;
			if(lastMaxGanancia == dp[i][j].ganancia){
				cajas[i] = j + 1;
				lastMaxGanancia = dp[i][j].ganancia - dp[i][j].real_ganancia;
				break;
			}
		}
	}
	
	for(int i = 0; i < A; i++)
		fout << cajas[i] << " ";
	fout << endl;
	
	return 0;
}
