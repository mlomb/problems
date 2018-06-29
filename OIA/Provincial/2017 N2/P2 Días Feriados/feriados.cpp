#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
	//ifstream cin("input.in");
	
	int N, D, F;
	cin >> N >> D >> F;
	
	vector<bool> feriados(D + 1, false);
	int feriado;
	for(int i = 0; i < N; i++){
		cin >> feriado;
		feriados[feriado - 1] = true;
	}
	
	int best = F;
	
	int i = 0;
	int clase = feriados[0] ? 0 : 1;
	for(int j = 1; j < D + 1; j++){
		best = max(best, j - i);
		
		if(!feriados[j]) {
			clase++;
			
			while(clase > F) {
				if(!feriados[i])
					clase--;
				i++;
			}
		}
	}
	
	cout << best << endl;
	
	return 0;
}