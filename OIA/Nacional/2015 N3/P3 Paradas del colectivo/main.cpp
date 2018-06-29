#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void combine(int position, int start, int max, vector<int>& combination) {
	if (position >= combination.size()) {
		for(int i : combination)
			cout << i << " ";
		cout << endl;
		return;
	}
	
	for (int i = start; i < max; i++) {        
		combination[position] = i;
		
		combine(position + 1, i + 1, max, combination);
	}
}

int paradas(int N, int P, int M, int T, const vector< vector<int> >& esquinas){
	int worst = 3;
	
	vector<int> weights;
	weights.resize(N);
	int pos = 0;
	for(vector<int> esq : esquinas){
		int w = abs(esq[1] - P) / 2;
		pos = esq[0] / 2;
		if(w > weights[pos])
			weights[pos] = w;
	}
	
	for(int i : weights){
		cout << i << " ";
	}
	cout << endl;
	
	vector<int> combination;
	for(int i = 0; i < M; i++)
		combination.push_back(0);
	combine(0, 0, N, combination);
	
	return worst * 100;
}

int main() {
	ifstream file("paradas.in");
	string line;
	stringstream ss;
	while(getline(file, line)){
		if(line[0] == '#')
			continue;
		ss << line << "\n";
	}
	istringstream iss(ss.str());
	
	int N, P, M, T;
	iss >> N >> P >> M >> T;
	vector< vector<int> > esquinas = vector< vector<int> >(T, vector<int>(2));
	
	for(int i = 0; i < T; i++)
		iss >> esquinas[i][0] >> esquinas[i][1];
	
	int result = paradas(N, P, M, T, esquinas);
	
	cout << "El pueblo con N=" << N << ", P=" << P << ", M=" << M << ", T=" << T << " hace caminar " << result << " metros." << endl;
	
	return 0;
}
