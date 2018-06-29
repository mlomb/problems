#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


static const char letters[] = "abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(letters) - 1;

char genRandom()
{
	return letters[rand() % stringLength];
}

int main() {
	ofstream fout("rayuela_stress.in");

	int D = 100, P = 10000;
	fout << D << " " << P << endl;

	for (int fil = 0; fil < D; fil++) {
		for (int col = 0; col < D; col++) {
			fout << (char)('a' + rand() % 26) << " " << (rand() % 70) << " ";
		}
		fout << endl;
	}

	for (int i = 0; i < P; i++) {
		for (int j = 0; j < 20; j++)
			fout << genRandom();
		fout << endl;
	}

	return 0;
}