#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(){
	ifstream file("EJ1.txt");
	
	string game;
	file >> game;
	int mygame[27];
	
	int dicCount;
	file >> dicCount;
	string dic;
	int count = 0;
	
	for(int i = 0; i < dicCount; i++){
		file >> dic;
		for(int j = 0; j <= 26; j++)
			mygame[j] = 0;
		for(int j = 0; j < game.size(); j++){ // Refill
			if(game[j] == 'Ñ')
				mygame[26]++;
			else
				mygame[game[j] - 65]++;
		}
		
		bool found = true;
		for(int j = 0; j < dic.size(); j++){
			int c = 0;
			if(dic[j] == 'Ñ'){
				mygame[26]--;
				c = mygame[26];
			} else {
				mygame[dic[j] - 65]--;
				c = mygame[dic[j] - 65];
			}
			if(c < 0){
				found = false;
				break;
			}
		}
		if(found){
			count++;
			cout << dic << endl;
		}
	}
	if(count == 0)
		cout << "NO SE PUEDE FORMAR NINGUNA" << endl;
	
	return 0;
}
