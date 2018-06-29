#include <iostream>
#include <math.h>

using namespace std;

bool isExact(double a, double b){
	double r = a / b;
	return r == (int)r;
}

int main(){
	int N;
	cin >> N;
	
	#define CRIBA_SIZE 110
	bool criba[CRIBA_SIZE];
	
	for(int i = 0; i < CRIBA_SIZE; i++)
		criba[i] = false;
		
	for(int i = 0; i < CRIBA_SIZE; i += 3)
		criba[i] = true;
	for(int i = 0; i < CRIBA_SIZE; i += 7)
		criba[i] = true;
	
	for(int i = 0; i < CRIBA_SIZE; i++){
		if(!criba[i]){
			bool val = false;
			if(i > 3 && criba[i - 3]) val = true;
			if(i > 7 && criba[i - 7]) val = true;
			criba[i] = val;
		}
	}
	
	int x;
	for(int i = 0; i < N; i++){
		cin >> x;
		cout << (criba[x] ? "YES" : "NO") << endl;
	}
	
	return 0;
}
