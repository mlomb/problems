#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

void initMap(int N, char** map) {
	for(int i = 0; i < N; i++)
		map[i] = new char[N];
}

void printMap(int N, char** map){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++)
			cout << map[i][j];
		cout << endl;
	}
	cout << endl;
}

int paint(int x, int y, int N, char** map, char cFrom, char cTo) {
	if(map[y][x] != cFrom)
		return 0;
		
	map[y][x] = cTo;
	
	cout << "X: " << x << ", Y: " << y << ", Cfrom: " << cFrom << ", Cto: " << cTo << endl;
	printMap(N, map);
	
	int count = 0;
	if(x < N)
		count += paint(x + 1, y, N, map, cFrom, cTo);
		
	return count;
}

int main() {
	ifstream file("repintar.in");
	
	int N;
	file >> N;
	
	char** map = new char*[N];
	initMap(N, map);
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			file >> map[i][j];
	
	vector<char> changes;
	
	char*** maps = new char**[2];
	maps[0] = new char*[N];
	maps[1] = new char*[N];
	
	initMap(N, maps[0]);
	initMap(N, maps[1]);
		
	int count[2] = { 0, 0 };
	const char l[] = { 'V', 'A', 'R' };
	do {
		int j = 0;
		for(int i = 0; i < 3; i++){
			char c = l[i];
			cout << map << ", " << maps[0] << ", " << maps[1] << endl;
			cout << map[0][0] << " = " << c << endl;
			if(map[0][0] != c){
				memcpy(maps[j], map, N * N * sizeof(char));
				
				maps[j][0][0] = c;
				//count[j] = paint(0, 0, N, maps[j], map[0][0], c);
				
				j++;
			}
		}
		
		cout << "choosen" << endl;
		
		int best = 0;
		if(count[1] > count[0])
			best = 1;
		
		map = maps[best];
		//changes.push_back(l[best]);
	} while(false);
	
	cout << changes.size() << endl;
	for(char c : changes)
		cout << c;
	cout << endl;
	
	return 0;
}
