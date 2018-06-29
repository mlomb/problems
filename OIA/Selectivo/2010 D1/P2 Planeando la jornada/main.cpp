#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define INF 999999999

using namespace std;

struct Cliente {
	int id;
	int x = 0, y = 0;
	int hour = 0;
	int patacones = 0;
	
	// dp
	int maxP = 0; // patacones maximo
	int before = -1; // cliente anterior
};

int main() {
	ifstream fin("negocios.in");
	
	int N;
	fin >> N;
	vector<Cliente> clientes;
	clientes.resize(N);
	
	for(int i = 0; i < N; i++){
		clientes[i].id = i + 1;
		fin >> clientes[i].x >> clientes[i].y >> clientes[i].hour >> clientes[i].patacones;
		
		if(abs(clientes[i].x) + abs(clientes[i].y) > clientes[i].hour)
			clientes[i].maxP = -INF;
		else
			clientes[i].maxP = clientes[i].patacones;
	}

	sort(clientes.begin(), clientes.end(), [](const Cliente& a, const Cliente& b){
		return a.hour < b.hour;
	});

	for(int i = 0; i < N; i++) {
		Cliente& c = clientes[i];
		
		for(int j = 0; j < i; j++) {
			Cliente& c_other = clientes[j];
			
			int dist = abs(c.x - c_other.x) + abs(c.y - c_other.y);
			
			if(c_other.hour + 3 + dist <= c.hour) {
				if(c_other.maxP + c.patacones > c.maxP) {
					c.maxP = c_other.maxP + c.patacones;
					c.before = j;
				}
			}
		}
	}
	
	int max = 0, max_i = -1;
	int i = 0;
	for(Cliente& c : clientes){
		if(c.maxP > max){
			max = c.maxP;
			max_i = i;
		}
		i++;
		//cout << "---" << endl;
		//cout << "ID: " << c.id << " X: " << c.x << " Y: " << c.y << endl;
		//cout << "HOUR: " << c.hour << " PATACONES: " << c.patacones;
		//cout << " MAX_P: " << c.maxP << " BEFORE: " << c.before << endl;
	}
	
	vector<int> visitas;
	while(max_i >= 0) {
		visitas.push_back(clientes[max_i].id);
		max_i = clientes[max_i].before;
	}
	
	reverse(visitas.begin(), visitas.end());
	
	ofstream fout("negocios.out");
	fout << max << endl;
	for(int& i : visitas)
		fout << i << " ";
	fout << endl;
	
	return 0;
}
