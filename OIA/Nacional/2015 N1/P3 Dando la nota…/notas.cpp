#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream input("notas.in");
	
	int length;
	input >> length;
	
	char notas[length];
	for(int i = 0; i < length; i++)
		input >> notas[i];
	
	char note;
	int p1_bad = -1, p2_bad = -1;
	int p1_ok = 0, p2_ok = 0;
	
	for(int i = 0; i < length; i++){
		input >> note;
		if(note != notas[i]){
			if(p1_bad == -1)
				p1_bad = (i + 1);
		} else
			p1_ok++;
	}
	if(p1_bad == -1)
		p1_bad = length + 1;
	
	for(int i = 0; i < length; i++){
		input >> note;
		if(note != notas[i]){
			if(p2_bad == -1)
				p2_bad = (i + 1);
		} else
			p2_ok++;
	}
	if(p2_bad == -1)
		p2_bad = length + 1;
	
	bool win = false; // 1
	if(p1_ok == p2_ok){ // Tie
		win = p2_bad > p1_bad;
	} else if(p2_ok > p1_ok)
		win = true;
	
	ofstream output("notas.out");
	
	output << (win ? 2 : 1) << endl;
	output << (win ? p2_ok : p1_ok) << endl;
	output << (win ? p2_bad : p1_bad) << endl;
	
	cout << (win ? 2 : 1) << endl;
	cout << (win ? p2_ok : p1_ok) << endl;
	cout << (win ? p2_bad : p1_bad) << endl;

	
	return 0;
}
