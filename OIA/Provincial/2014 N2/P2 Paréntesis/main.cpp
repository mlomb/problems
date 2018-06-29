#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool verify(string& w){
	//cout << w << endl;
	
	int open = 0;
	for(int i = 0; i < w.size(); i++){
		if(w[i] == '('){
			open++;
		} else { // ')'
			if(open <= 0)
				return false;
			else
				open--;
		}
	}
	if(open != 0)
		return false;
	return true;
}

void check(string& w){
	if(verify(w))
		cout << "V" << endl;
	else
		cout << "I" << endl;
}

void swapBrackets(string& w, int i){
	if(w[i] == '(')
		w[i]++;
	else
		w[i]--;
}

int main(){
	ifstream file("EJ3.txt");
	
	string w;
	file >> w;
	
	check(w);
	
	int modifications, currentSwap;
	file >> modifications;
	
	for(int i = 0; i < modifications; i++){
		file >> currentSwap;
		currentSwap--;
		swapBrackets(w, currentSwap);
		check(w);
	}
	
	system("pause");
	
	return 0;	
}
