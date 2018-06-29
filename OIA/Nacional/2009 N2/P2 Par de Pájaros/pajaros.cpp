#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define Y_SIZE 305

using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	ifstream fin("pajaros.in");
	int I;
	fin >> I;
	I++;
	
	vector<int> pajara_path;
	pajara_path.push_back(0);
	for(int i = 0; i < I; i++){
		int a;
		fin >> a;
		pajara_path.push_back(a);
	}
	
	int** pajaroDP = new int*[Y_SIZE];
	for(int i = 0; i < Y_SIZE; i++){
		pajaroDP[i] = new int[I];
		for(int j = 0; j < I; j++)
			pajaroDP[i][j] = 1 << 20;
	}
	

	pajaroDP[0][0] = 0;
	for(int col = 1; col < I; col++){
		int alturaPajara = pajara_path[col];
		for(int fil = 0; fil < Y_SIZE; fil++){
			int bestLast = 1 << 20;
			if(fil - 1 >= 0)
				bestLast = min(bestLast, pajaroDP[fil - 1][col - 1]);
			if(fil + 1 < Y_SIZE)
				bestLast = min(bestLast, pajaroDP[fil + 1][col - 1]);
			
			if(bestLast == 1 << 20)
				continue;
			
			//cout << bestLast << " + abs(" << fil << "-" << alturaPajara << ")" << endl;
			pajaroDP[fil][col] = bestLast + abs((fil + 0) - alturaPajara);
		}
	}
	
	/*
	for(int j = 0; j < I; j++)
		cout << pajara_path[j] << "  ";
	cout << endl;
	for(int i = 0; i < Y_SIZE; i++){
		for(int j = 0; j < I; j++){
			cout << (pajaroDP[i][j] > 1 << 20 - 10 ? -1 : pajaroDP[i][j]) << " ";
		}
		cout << endl;
	}
	*/
	
	ofstream fout("pajaros.out");
	
	int dist = 1 << 20;
	int minFil = 0;
	for(int fil = Y_SIZE - 1; fil >= 0; fil--){
		if(pajaroDP[fil][I - 1] < dist){
			dist = pajaroDP[fil][I - 1];
			minFil = fil;
		}
	}
	fout << dist << "\n";
	
	return 0;
}