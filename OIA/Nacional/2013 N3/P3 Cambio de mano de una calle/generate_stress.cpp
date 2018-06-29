#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int random_int(int min, int max)
{
   return min + rand() % (max+1 - min);
}

int main(){
	ofstream file("invertir_stress.in");
	
	int E = 2000;
	int C = 25000;
	
	file << E << " " << 1 << " " << (E - 2) << endl;
	file << C << endl;
	
	for(int i = 0; i < C; i++){
		int x = random_int(1, E);
		int y = random_int(1, E);
		int w = random_int(1, 50);
		
		file << x << " " << y << " " << w << endl;
	}
	
	return 0;
}
