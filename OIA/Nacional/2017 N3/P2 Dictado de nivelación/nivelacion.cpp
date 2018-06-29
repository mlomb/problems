#include <string>
#include <iostream>
#include <vector>

using namespace std;

int  nivelacion(string palabra)
{
	int size = palabra.length();
	vector< vector<int> > dp(size, vector<int>(size, 0));
	
	for(int i = size - 2; i >= 0; i--) {
		for(int j = i + 1; j < size; j++) {
			if(palabra[i] == palabra[j])
				dp[i][j] = dp[i + 1][j - 1];
			else
				dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
		}
	}
	
	/*
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
	*/
	
	return dp[0][size - 1];
}