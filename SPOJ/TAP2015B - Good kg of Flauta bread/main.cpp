#include <iostream>
#include <fstream>

typedef long long int lli;

using namespace std;

int main() {
#if LOCAL
	ifstream cin("input.in");
#endif
	
	lli K, L;
	
	while(cin >> L >> K){
		
		// hacemos busqueda binaria sobre un numero T que representa
		// el numero maximo de triangulos unitarios en una misma seccion
				
		lli lo = 0, hi = L * L + 1; // todos los numeros impares hasta x sumados = x * x
		while(hi - lo > 1) {
			lli T = (lo + hi) / 2;
			
			lli sum = 0, secciones = 0;
			for(lli i = 1; i < L * 2; i += 2) {
				sum += i;
				if(sum >= T) {
					secciones++;
					sum = 0;
				}
			}
			
			//cout << "T: " << T << " -- secciones: " << secciones << endl;
			
			if(secciones >= K)
				lo = T;
			else
				hi = T;
		}
		
		cout << lo << endl;
	}
	
	return 0;
}
