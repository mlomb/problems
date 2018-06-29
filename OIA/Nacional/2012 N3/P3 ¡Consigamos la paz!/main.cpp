#include <iostream>
#include <fstream>

using namespace std;

void tagIslands(bool** mapa, int** islas, int N, int fil, int col, int id) {
	if(fil < 0 || fil >= N || col < 0 || col >= N)
		return;
	if(!mapa[fil][col])
		return;
	if(islas[fil][col] != -1)
		return;
	
	islas[fil][col] = id;
	
	tagIslands(mapa, islas, N, fil, col + 1, id);
	tagIslands(mapa, islas, N, fil, col - 1, id);
	tagIslands(mapa, islas, N, fil + 1, col, id);
	tagIslands(mapa, islas, N, fil - 1, col, id);
}

void eatIsland(bool** mapaMarcado, int** islas, int N, int fil, int col, int id) {
	if(fil < 0 || fil >= N || col < 0 || col >= N)
		return;
	if(islas[fil][col] != id)
		return;
	if(mapaMarcado[fil][col])
		return;
	
	mapaMarcado[fil][col] = true;
	
	eatIsland(mapaMarcado, islas, N, fil, col + 1, id);
	eatIsland(mapaMarcado, islas, N, fil, col - 1, id);
	eatIsland(mapaMarcado, islas, N, fil + 1, col, id);
	eatIsland(mapaMarcado, islas, N, fil - 1, col, id);
}

void poligonal(bool** mapaMarcado, int fil, int col, int N, char last){
	//std::cout <<endl<< fil << ", " << col << ": ";
	if(fil == -1 && col == N)
		return;
	// voy al norte si:
	bool n = fil >= 0 && // no me voy fuera del mapa para arriba
			 last != 'S' && ( // no vengo del sur
			 (col == 0 && mapaMarcado[fil][col]) || // estoy pegado al borde izquierdo y estoy marcado
			 (col >= N && !mapaMarcado[fil][col - 1]) || // estoy pegado al borde derecho y no estoy marcado
			 (col > 0 && mapaMarcado[fil][col] != mapaMarcado[fil][col - 1]) // si no estoy en el borde y a mis lados las marcas no coinciden
			 );
	if(n){
		cout << 'N';
		poligonal(mapaMarcado, fil - 1, col, N, 'N');
	}
	else{
		bool e = col < N && // no me voy fuera por derecha
				 last != 'O' && ( // no vengo del oeste
				 (fil == -1 && mapaMarcado[fil + 1][col]) || // estoy pegado arriba y tengo un uno abajo
				 (fil == N - 1 && !mapaMarcado[fil - 1][col]) || // estoy pegado abajo y tengo un cero arriba
				 (fil >= 0 && fil < N && mapaMarcado[fil][col] != mapaMarcado[fil + 1][col]) // no estoy en el borde y mis lados las marcas son distintas
				 );
		if(e){
			cout << 'E';
			poligonal(mapaMarcado, fil, col + 1, N, 'E');
		} else {
			bool s = fil < N && // no me salgo del mapa para abajo
					 last != 'N' && ( // no vengo del norte
					 mapaMarcado[fil + 1][col] != mapaMarcado[fil + 1][col - 1]
					 );
			if(s){
				cout << 'S';
				poligonal(mapaMarcado, fil + 1, col, N, 'S');
			} else {
				// descarte :)
				cout << 'O';
				poligonal(mapaMarcado, fil, col - 1, N, 'O');
			}
		}
	}
}

int main(){
	// DISCLAIMER:
	// Este es un ejercicio largo y aburrido ;)
	// pero no tanto como billar >_>
	
	ifstream cin("litigio.in");
	
	int N;
	cin >> N;
	
	bool** mapa = new bool*[N];
	bool** mapaMarcado = new bool*[N];
	int** islas = new int*[N];
	char bit;
	for(int i = 0; i < N; i++){
		mapa[i] = new bool[N];
		mapaMarcado[i] = new bool[N];
		islas[i] = new int[N];
		for(int j = 0; j < N; j++){
			cin >> bit;
			mapaMarcado[i][j] = false;
			mapa[i][j] = bit == '1';
			islas[i][j] = bit == '1' ? -1 : 0; // -1 = isla sin etiquetar, 0 = agua
		}
	}
	
	// 1. Etiquetar las islas
	int id = 1;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(mapa[i][j] && islas[i][j] == -1)
				tagIslands(mapa, islas, N, i, j, id++);
		}
	}
	
	// 2. Expandir las islas
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			// Si soy una casilla de agua
			if(!mapa[i][j]){
				// De todas las de los costados...
				for(int dx = (i > 0 ? -1 : 0); dx <= (i < N - 1 ? 1 : 0); ++dx){
					for(int dy = (j > 0 ? -1 : 0); dy <= (j < N - 1 ? 1 : 0); ++dy){
						// Si es de terreno
						if(mapa[i + dx][j + dy])
							islas[i][j] = islas[i + dx][j + dy];
					}
				}
				
			}
		}
	}
	
	// 3. Comer islas
	// (notese que de abajo para arriba)
	// id = cantidad de islas
	int islasComidas = 0;
	for(int i = N - 1; i >= 0; i--){
		for(int j = N - 1; j >= 0; j--){
			// Si es agua, nos la comemos de una, ya fue
			if(!mapa[i][j]){
				mapaMarcado[i][j] = true;
			} else {				
				// Sino bueno, nos comemos toda esta isla recursivamente
				islasComidas++;
				eatIsland(mapaMarcado, islas, N, i, j, islas[i][j]);
				
				if(islasComidas == id / 2){
					i = 0; // romper el for exterior
					break;
				}
			}
		}
	}
	
	/*
	// DEBUG
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cout << mapaMarcado[i][j] << " ";
		}
		cout << endl;
	}
	*/
	
	// 4. Generar la poligonal
	poligonal(mapaMarcado, N - 1, 0, N, 'N');
	cout << endl;
	
	// 5. enjoy
	
	return 0;
}
