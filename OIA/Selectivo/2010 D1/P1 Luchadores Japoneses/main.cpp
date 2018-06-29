#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

#define LSB(i) (i & (-i))

const int N = 11000000 + 10;
int ftree[N];

void add(int index, int value){
	while(index <= N){
		ftree[index] += value;
		index += LSB(index);
	}
}

int get(int index){
	int result = 0;
	while(index > 0){
		result += ftree[index];
		index -= LSB(index);
	}
	return result;
}

struct Participante {
	int i;
	int P, H;
	int sum;
};

bool sortH(const Participante& a, const Participante& b) {
	if(a.H == b.H)
		return a.P < b.P;
	else
		return a.H < b.H;
}
bool sortInd(const Participante& a, const Participante& b) {
	return a.i < b.i;
}

int main(){
	ifstream cin("sumo.in");
#ifndef LOCAL
	ofstream cout("sumo.out");
#endif
	
	int L;
	cin >> L;
	
	vector<Participante> pps(L);
	for(int i = 0; i < L; i++){
		pps[i].sum = 0;
		pps[i].i = i;
		cin >> pps[i].P >> pps[i].H;
	}
	
	sort(pps.begin(), pps.end(), sortH);
	
	for(Participante& p : pps) {
		p.sum = get(p.P);
		add(p.P, 1);
	}
	
	sort(pps.begin(), pps.end(), sortInd);
	
	for(const Participante& p : pps)
		cout << p.sum << endl;
	
	return 0;
}
