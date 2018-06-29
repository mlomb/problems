#include <iostream>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

struct Tank;

struct Pipe {
	int D;
	Tank* output;
};

struct Tank {
	int V;
	vector<Pipe*> outputPipes;
};

// retorna lo que uso el tanque 'hijo'
int fillTank(Tank* tank, int agua, int& llenos) {
	int atot = agua;
	int current = 0;
	
	//cout << "Tanque: " << tank->V << endl;
	
	int prev = tank->V;
	for(Pipe* p : tank->outputPipes) {
		int n = (prev - p->D);
		n = min(n, agua);
		//cout << " Pipe: " << p->D << " -- " << n << ", " << agua << ", " << current << endl;
		agua -= n;
		current += n;
		
		if(agua > 0){
			int usado = fillTank(p->output, agua, llenos);
			agua -= usado;
			prev = p->D;
		}
		else
			break;
	}
	
	// hasta el tope
	if(agua > 0) {
		int menor = tank->V - current;
		int hm = min(agua, menor);
		agua -= hm;
		current += hm;
	}
	
	if(current > 0)
		llenos++;
		
	return atot - agua;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
	//ifstream fcin("input2.in");
	
	int T;
	cin >> T;
	vector<Tank*> tanks = vector<Tank*>(T);
	
	for(int i = 0; i < T; i++){
		Tank* t = new Tank();
		cin >> t->V;
		tanks[i] = t;
	}
	
	int T1, D, T2;
	for(int i = 0; i < T - 1; i++){
		cin >> T1 >> D >> T2;
		T1--;
		T2--;
		Pipe* p = new Pipe();
		p->D = D;
		p->output = tanks[T2];
		tanks[T1]->outputPipes.push_back(p);
	}
	
	for(Tank* t : tanks) {
		sort(t->outputPipes.begin(), t->outputPipes.end(), [](const Pipe* a, const Pipe* b) {
			return a->D > b->D;
		});
	}
	/*
	for(Tank* t : tanks) {
		cout << "Tanque: V= " << t->V << endl;
		for(Pipe* p : t->outputPipes) {
			cout << "	Tuberia: D=" << p->D << endl;
		}
	}
	*/
	int Q, K;
	int result;
	cin >> Q;
	for(int i = 0; i < Q; i++){
		cin >> K;
		result = 0;
		fillTank(tanks[0], K, result);
		cout << result << " ";
	}
	cout << "\n";
	
	return 0;
}