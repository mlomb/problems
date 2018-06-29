// La siguiente linea se usa para compilar en Geany con F9. Compilando de otra forma, podria ser necesario quitarla.
#include "caminito.cpp"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void caminito(string &baldosas);

int main()
{
	ifstream cin("ejemplo.in");
	
    string baldosas;
    cin >> baldosas;
    caminito(baldosas);
    cout << baldosas << endl;
    return 0;
}
