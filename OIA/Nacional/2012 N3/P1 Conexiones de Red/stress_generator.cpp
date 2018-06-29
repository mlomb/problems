#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int randm(int min = 1, int max = 1000000) {
	return min + (rand() % static_cast<int>(max - min + 1));
}

int main() {
	ofstream file("conectar_stress.in");
	
	for(int i = 0; i < 200000; i++){
		file << (randm(0, 1) == 1 ? 'C' : 'P') << " " << randm() << " " << randm() << endl;
	}
	file << "F" << endl;
	
	return 0;
}
