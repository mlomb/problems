#include <vector>
#include <iostream>

using namespace std;

void continuar(int last_parada, int bateria, vector<int>& paradas, const int E, const vector<int>& ubicacion, const vector<int>& autonomia) {
	
	for(int i = last_parada + 1; i < E; i++) {
		bateria -= ubicacion[i] - ubicacion[i - 1];
		if(bateria < 0) {
			// tengo que parar para poder llegar a la parada i
			int best = 0, best_parada = -1;
			
			for(int j = last_parada + 1; j < i; j++) {
				int bat = autonomia[j] - (ubicacion[i] - ubicacion[j]);
				if(bat >= best) {
					best = bat;
					best_parada = j;
				}
			}
			
			if(best_parada == -1) {
				paradas.clear();
				return;
			}
			
			paradas.push_back(ubicacion[best_parada]);
			continuar(best_parada, autonomia[best_parada], paradas, E, ubicacion, autonomia);
			return;
		}
	}
	
	paradas.push_back(ubicacion[E - 1]);
}

vector<int> electromovil(int E, vector<int> ubicacion, vector<int> autonomia)
{
    vector<int> paradas;
    
    continuar(0, autonomia[0], paradas, E, ubicacion, autonomia);
    
    return paradas;
}
