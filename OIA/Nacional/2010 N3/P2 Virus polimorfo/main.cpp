#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>

using namespace std;

int N, M;

bool modify(int code_id, int* sequence, int delta) {
	if(code_id >= 0 && code_id < M) {
		sequence[code_id] += delta;
		return true;
	}
	return false;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	ifstream fin("polimorfo.in");
	
	fin >> N >> M;
	
	vector<int> code;
	code.resize(N);
	int num;
	for(int i = 0; i < N; i++){
		fin >> num;
		num--;
		code[i] = num;
	}
	
	vector<int> result;
	int* sequence = new int[M];
	memset(sequence, 0, M * sizeof(int));
	
	int end = 0;
	bool succ = true;
	do {
		int start = end - M;
		if(start >= 0)
					 modify(code[start], sequence, -1);
		bool valid = modify(code[end], sequence, 1);
		
		if(valid){
			succ = true;
			for(int i = 0; i < M; i++){
				if(sequence[i] != 1){
					succ = false;
					break;
				}
			}
			if(succ)
				result.push_back(end - M + 2);
		}
		
		end++;
	} while(end < N);
	
	
	ofstream fout("polimorfo.out");
	fout << result.size() << endl;
	
	if(result.size() <= 10) {
		for(int i : result)
			fout << i << " ";
	} else {
		for(int i = 0; i < 5; i++)
			fout << result[i] << " ";
		
		for(int i = result.size() - 5; i < result.size(); i++)
			fout << result[i] << " ";
	}
	
	fout << "\n";
	
	return 0;
}
