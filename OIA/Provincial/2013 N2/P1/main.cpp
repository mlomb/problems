#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

int teams = 0;

void combineTeams(int container[], int start, int end, int position, int size, vector< vector<bool> > enemies) {
	if(position >= size){
		for(int x = 0; x < size; x++){
			for(int y = x; y < size; y++){
				if(enemies[container[x]][container[y]])
					return;
			}
		}
		teams++;
		return;
	}
	
	for(int i = start; i <= end; i++){
		container[position] = i;
		
		combineTeams(container, i + 1, end, position + 1, size, enemies);
	}
}

int main() {
	int count, eCount;
	ifstream file("EJ4.txt");
	
	file >> count >> eCount;
	cout << "Chicos: " << count << endl << "Peleas: " << eCount << endl;
	
	int x, y;
	vector< vector<bool> > enemies(count);
	for(int i = 0; i < count; i++)
		enemies[i] = vector<bool>(count);
	
	while(file >> x >> y){
		enemies[x][y] = true;
		enemies[y][x] = true;
		cout << x << " con " << y << endl;
	}

	int container[4];
	combineTeams(container, 1, count - 1, 0, 4, enemies);
	
	cout << "Equipos posibles: " << teams << endl;
	
	system("PAUSE");
	return teams;
}
