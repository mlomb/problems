#include <fstream>
#include <cassert>
#include <limits.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>

using namespace std;

const int MAX = 200000 + 5;

#define DBG 0

int main() {
	ifstream fin("adn.in");
	ofstream fout("adn.out");
	
	int* dp_last;
	int* dp_current;
	
	dp_last = new int[MAX];
	dp_current = new int[MAX];
	
	int N, M, K;
	fin >> N >> M >> K;

	string adn_N, adn_M;
	fin >> adn_N >> adn_M;
	
	// first row
	for(int i = 0; i < M + 1; i++) dp_last[i] = i;
	
#if DBG
	for(int j = 0; j < M + 1; j++)
		cout << dp_last[j] << " ";
	cout << endl;
#endif
	
	for(int i = 0; i < N; i++){
		dp_current[0] = i + 1;
		
		int lb = max(0, i - 2 * K - 1);
		int ub = min(M, i + 2 * K + 1);
		
		for(int j = lb; j < ub; j++){
			int val;
			if(adn_N[i] != adn_M[j])
				val = min(dp_last[j], min(dp_current[j], dp_last[j + 1])) + 1;
			else
				val = dp_last[j];
			
			dp_current[j + 1] = val;
		}
		
#if DBG
		for(int j = 0; j < M + 1; j++)
			cout << dp_current[j] << " ";
		cout << endl;
#endif
		
		swap(dp_current, dp_last);
	}
	
	if(dp_last[M] > K)
		fout << "Muy distintas." << endl;
	else
		fout << dp_last[M] << endl;

	return 0;
}
