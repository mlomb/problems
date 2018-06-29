#include <vector>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct Estacion {
	int id;
	int mm = 100, MM = -100;
};

int main() {
	ifstream fin("clima.in");
	
	int P;
	fin >> P;
	
	std::vector<Estacion> estaciones;
	
	int R, m, M;
	for(int i = 0; i < P; i++){
		Estacion e;
		e.id = i + 1;
		fin >> R;
		for(int j = 0; j < R; j++){
			fin >> m >> M;
			e.mm = min(e.mm, m);
			e.MM = max(e.MM, M);
		}
		estaciones.emplace_back(e);
	}
	
	// ---
	map<int, int> resultado; // id, no comparables
	
	for(const Estacion& e : estaciones){
		//cout << e.id << ", mm: " << e.mm << ", MM: " << e.MM << endl;
		int noComparable = 0;
		for(const Estacion& e_other : estaciones){
			if(e.id == e_other.id)
				continue;
			
			if((e.mm < e_other.mm && e.MM > e_other.MM) ||
			   (e.mm == e_other.mm && e.MM > e_other.MM) ||
			   (e.MM == e_other.MM && e.mm < e_other.mm)){ // e es mas hostil que e_other
				//std::cout << e.id << " es mas hostil que " << e_other.id << std::endl;
			} else if(e.MM == e_other.MM && e.mm == e_other.mm){
				//std::cout << e.id << " es igual de hostil que " << e_other.id << std::endl;
			} else {
				noComparable++;
			}
		}
		//cout << "No comparables: " << noComparable << endl << endl;
		if(noComparable < estaciones.size() - 1){
			resultado.insert(make_pair(e.id, noComparable));
		}
	}
	
	
	// ---
	ofstream fout("clima.out");
	for(auto& kv : resultado){
		fout << kv.first << " " << kv.second << endl;
	}
	
	return 0;
}
