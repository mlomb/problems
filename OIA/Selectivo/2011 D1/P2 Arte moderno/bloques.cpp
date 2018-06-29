#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef long long int lli;

const int MAX_N = 100000 + 50;

int T, K;
int current[MAX_N];
int target[MAX_N];

// x es el balance del deposito izquierdo
// si x es + entonces va a entregar cajas
lli cost(lli x) {
	lli balance = x;
	lli cost = abs(x) * K;
	
	for(int i = 0; i < T; i++){
		balance += current[i] - target[i];
		cost += abs(balance) * (i == T - 1 ? K : 1);
	}
	
	return cost;
}

int main() {
	ifstream cin("bloques.in");
	ofstream cout("bloques.out");
	
	cin >> T >> K;
	for(int i = 0; i < T; i++)
		cin >> current[i];
	for(int i = 0; i < T; i++)
		cin >> target[i];
	
	const lli bound = MAX_N * 1000;
	
	// binary search
	lli l = -bound, r = bound;
	while(r - l > 1) {
		lli mid = (l+r)/2;
		
		if(cost(mid) > cost(mid+1)) {
			l = mid;
		} else {
			r = mid;
		}
	}
	
	cout << cost(r) << endl;
	
	return 0;
}
