#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

void investigar(int S, int L, int K, int* largo, int* fin, int* cuantas){
	*largo = 0;
	*fin = 0;
	*cuantas = 0;
	
	vector<int> recortada;
	long long current = S;
	while(true){
		recortada.push_back(current);
		
		if(current % 2 == 0)
			current /= 2;
		else {
			current *= 3;
			current++;
		}
		
		// 1
		if(recortada.size() >= L)
			break;
		// 2
		if(current > INT_MAX)
			break;
		// 3
		for(int i : recortada)
			if(i == current)
				break;
	}
	
	*largo = recortada.size();
	*fin = recortada.back();
	
	/*
	int beforeSeed = 0;
	if(S % 2 == 0)
		beforeSeed = (S - 1) / 3;
	else
		beforeSeed = S * 2;	
	recortada.insert(recortada.begin() + 0, beforeSeed);
	*/
	
	/*
	for(int i : recortada)
		cout << i << " ";
	cout << endl;
	*/
	
	int descensos = 0;
	for(int i = 1; i < recortada.size(); i++) {	
		int previous = recortada[i - 1];
		int next = recortada[i];
		
		if(previous > next)
			descensos++;
		else {
			if(descensos == K)
				(*cuantas)++;
			descensos = 0;
		}
	}
	
	// Last one
	if(descensos == K)
		(*cuantas)++;
}

int main() {
	int S = 0, L = 0, K = 0;
	
	if(true){
		S = 29;
		L = 13;
		K = 2;
	} else {
		S = 52;
		L = 6;
		K = 2;
	}
	
	int largo, fin, cuantas;
	
	investigar(S, L, K, &largo, &fin, &cuantas);
	
	cout << "S=" << S << " L=" << L << " K=" << K << " largo=" << largo << " fin=" << fin << " cuantas=" << cuantas << endl;
	
	return 0;
}
