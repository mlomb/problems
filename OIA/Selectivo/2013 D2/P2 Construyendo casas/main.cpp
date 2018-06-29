#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

const int INF = 9999999;
const int MAX_Y = 200000 + 10;
const int MAX_X = 40 + 1;
const int MIN_K = 1;

struct Estado {
	int best;
	int direction;
};

Estado dp[200000][MAX_X];

int main() {
	ifstream cin("casas.in");
	ofstream fout("casas.out");
	
	int X, Y, C;
	cin >> X >> Y >> C;
	
	vector<int> conexiones(C);
	for(int i = 0; i < C; i++){
		cin >> conexiones[i];
	}
	
	for(int i = 0; i < C; i++){
		int P = conexiones[i];
		int mx = X / 2;
		
		// left max
		if(i == 0) mx = min(mx, P);
		else mx = min(mx, P - conexiones[i - 1] - MIN_K);
		
		// right max
		if(i == C - 1) mx = min(mx, Y - P);
		else mx = min(mx, conexiones[i + 1] - P - MIN_K);
		
		for(int k = MIN_K; k <= mx; k++) {
			int last_compatible_best = 0; // last *compatible* best
			int last_compatible_k = 0;
			
			if(i > 0){
				int last_compatible_max = min(P - conexiones[i - 1] - k, X / 2);
				
				for(int j = MIN_K; j <= last_compatible_max; j++){
					if(dp[i - 1][j].best > last_compatible_best) {
						last_compatible_best = dp[i - 1][j].best;
						last_compatible_k = j;
					}
				}
			}
			
			dp[i][k] = { last_compatible_best + (k * 2) * (k * 2), last_compatible_k };
		}
	}
	
	/*
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			cout << dp[j][19 - i].best << " ";
		}
		cout << endl;
	}
	*/
	
	int b = 0;
	int b_k = 0;
	for(int i = 0; i < MAX_X; i++) {
		if(dp[C - 1][i].best > b) {
			b = dp[C - 1][i].best;
			b_k = i;
		}
	}
	
	fout << dp[C - 1][b_k].best << endl;
	
	int r_i = 0;
	vector<int> result;
	result.resize(C);
	result[r_i++] = b_k;
	for(int i = C - 1; i > 0; i--){
		const Estado& e = dp[i][b_k];
		b_k = e.direction;
		result[r_i++] = b_k;
	}
	
	for(auto it = result.rbegin(); it != result.rend(); it++)
		fout << (*it) * 2 << endl;
	
	return 0;
}
