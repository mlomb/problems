#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream file("TEST.txt");
	
	int target;
	file >> target;

	int bonus = 1;
	int jumps = 0;
	int position = 0;
	
	while(position < target - 1){
		if(position + bonus < target){
			position += bonus;
			bonus *= 2;
		} else {
			position++;
			bonus = 1;
		}
		jumps++;
	}
	cout << jumps << endl;
	
	return 0;
}
