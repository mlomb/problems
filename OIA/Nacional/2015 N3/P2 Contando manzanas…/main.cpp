#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int recorrido(int eo,int ns,int e,vector< vector<int> >esquinas, int c, vector< vector<int> >conexiones, int* perimetro, int* manzanas){
		
}

int main(){
	int eo, ns, e, c;
	ifstream file("recorrido.in");
	file >> eo >> ns >> e;
	vector< vector<int> >esquinas(e, vector<int>(2));
	
	for(int i = 0; i < e; i++)
		file >> esquinas[i][1] >> esquinas[i][0];
	
	file >> c;
	vector< vector<int> >conexiones(c, vector<int>(2));
	for(int i = 0; i < c; i++)
		file >> conexiones[i][0] >> conexiones[i][1];
	
	int p = 0, m = 0;
	recorrido(eo, ns, e, esquinas, c, conexiones, &p, &m);
	
	cout << "Archivo con " << e << " esquinas y " << c << " conexiones da perímetro " << p << " y manzanas " << m << "." << endl;
	
	return 0;
}
