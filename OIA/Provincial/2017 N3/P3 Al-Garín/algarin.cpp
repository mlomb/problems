#include <iostream>
#include <limits.h>
#include <vector>
#include <fstream>

using namespace std;

int m, n;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(NULL);

	cin >> m >> n;
	
	char** map = new char*[m];
	int** joyasDP = new int*[m];
	
	int sf, sc;
	for(int i = 0; i < m; i++) {
		map[i] = new char[n];
		joyasDP[i] = new int[n];
		
		for(int j = 0; j < n; j++) {
			cin >> map[i][j];
			joyasDP[i][j] = map[i][j] == 'A' ? 0 : -1;
		}
	}
	
	for(int col = 1; col < n; col++) {
		for(int fil = 0; fil < m; fil++) {
			int joyas = joyasDP[fil][col - 1];
			if(fil - 1 >= 0)
				joyas = max(joyas, joyasDP[fil - 1][col - 1]);
			if(fil + 1 < m - 1)
				joyas = max(joyas, joyasDP[fil + 1][col - 1]);
			
			if(joyas == -1)
				continue;
			
			char c = map[fil][col];
			if(c == 'J')
				joyas++;
			else if(c == 'M'){
				if(joyas == 0)
					joyas = -1;
				else
					joyas = 0;
			}
			
			
			joyasDP[fil][col] = joyas;
		}
	}
	
	
	int maxJ = -1;
	for(int j = 0; j < m; j++)
		maxJ = max(maxJ, joyasDP[j][n - 1]);
	
	/*
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			cout << joyasDP[i][j] << " ";
		}
		cout << endl;
	}
	*/
	
	if(maxJ == -1)
		cout << "SIN SALIDA" << "\n";
	else
		cout << maxJ << "\n";
	
	return 0;
}