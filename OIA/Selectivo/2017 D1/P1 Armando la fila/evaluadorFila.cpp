// SOLO GEANY:
#include "fila.cpp"


#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// SOLO CODEBLOCKS:
// struct Fecha { int dia, mes,anno; };

int fila(vector<Fecha> orden, vector<int> &enojados);

int main()
{
	ifstream fin("fila.in");
	
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int C; fin >> C;
    vector<Fecha> v(C);
    for (int i=0;i<C;i++)
        fin >> v[i].dia >> v[i].mes >> v[i].anno;
    vector<int> enojados;
    cout << "Con una fila de " << C << " personas la maxima intensidad de enojo es " << fila(v, enojados) << " y su orden:" << endl;
    for (int i=0;i<int(enojados.size()); i++)
    {
        if (i) cout << " ";
        cout << enojados[i];
    }
    cout << endl;
    return 0;
}
