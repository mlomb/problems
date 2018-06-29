#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

char getAt(int x, int y){
	if(x == 6)
		return 'z';
	return 97 + (y - 1) * 5 + (x - 1);
}

int main(){
	int cantG, cantP;
	char c;
	ifstream file("EJ1.txt");
	
	file >> cantG >> cantP;
	
	//cout << cantG << " guardia(s), " << cantP << " palabra(s)." << endl;
	
	int f = 0;
	int count = 0;
	vector< vector<int> > data(cantG);
	
	file >> skipws >> c;
	while(count != cantG){
		file >> noskipws >> c;
		if(c == '*') f++;
		else {
			if(f == 0) continue;
			data[count].push_back(f);
			f = 0;
			if(c != '_') count++;
		}
	}
	
	string words[cantP];
	
	//cout << "Palabras: " << endl;
	for(int i = 0; i < cantP; i++){
		file >> skipws >> words[i];
		//cout << w << endl;
	}
	
	vector< vector<string> > result(cantG);
	
	for(int i = 0; i < cantG; i++){
		short nonfixed = 2 - (data[i].size() % 2);
		int fixedsize = data[i].size() - nonfixed;
		
		string fixed("");
		for(int j = nonfixed; j < data[i].size(); j+=2)
			fixed.push_back(getAt(data[i][j+1], data[i][j]));

		int x = nonfixed == 2 ? data[i][1] : data[i][0];
		int y = nonfixed == 2 ? data[i][0] : 1;

		for(int pi = 0; pi < cantP; pi++){
			for(int ci = words[pi].size() - 1; ci >= 0; ci--){
				int right = words[pi].size() - ci;
				if(right >= fixedsize){
					int maxX = 6;
					if(nonfixed == 2)
						maxX = x;
					for(int xx = x; xx <= maxX; xx++){
						for(int yy = y; yy <= 5; yy++){
							if(getAt(xx, yy) == words[pi][ci])
								result[i].push_back(words[pi]);
							if(xx == 6) // Hacer solo 1 z
								break;
						}
					}
					break;
				} else if(words[pi][ci] != fixed[fixedsize - right - 1]){
					break;
				}
			}
		}
	}
	
	for(int i = 0; i < cantG; i++){
		cout << result[i].size() << " ";
		for(int j = 0; j < result[i].size(); j++){
			cout << result[i][j] << " ";
		}
		cout << endl;
	}
	
	return 0;
}
