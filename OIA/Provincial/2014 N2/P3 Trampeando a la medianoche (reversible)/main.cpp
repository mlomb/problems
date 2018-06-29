#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

int main(){
	ifstream file("EJ2.txt");
	
	int count;	
	string w;
	vector< vector<string> > data(0);
	
	file >> count;
	
	for(int i = 0; i < count; i++){ // Todas las palabras de entrada
		file >> w;
		bool found = false;
		
		for(int j = 0; j < data.size(); ++j){ // Todos los circulos actuales
			if(data[j][0].size() != w.size())
				continue;
			int max = data[j][0].size() * 2;
			int equalCount = 0;
			/* Normal */
			for(int k = 0; k < max; k++){
				int rk = k % data[j][0].size();
				
				if(data[j][0][rk] == w[equalCount])
					equalCount++;
				else
					equalCount = 0;

				if(equalCount == w.size()){
					found = true;
					break;
				}
			}
			equalCount = 0;
			if(!found){
				/* Reverse */
				for(int k = max; k >= 0; k--){
					int rk = k % data[j][0].size();
					
					if(data[j][0][rk] == w[equalCount])
						equalCount++;
					else
						equalCount = 0;
	
					if(equalCount == w.size()){
						found = true;
						break;
					}
				}
			}
			if(found){
				data[j].push_back(w);
				break;
			}
		}
		
		if(!found){
			vector<string> circle = vector<string>();
			circle.push_back(w);
			data.push_back(circle);
		}
	}
	
	for(int i = 0; i < data.size(); i++){
		for(int j = 0; j < data[i].size(); j++){
			cout << data[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
