#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <tuple>

using namespace std;

struct Fecha
{
    int dia, mes,anno;
    
    bool operator>(const Fecha& b){
    	return make_tuple(anno, mes, dia) > make_tuple(b.anno, b.mes, b.dia);
	}
};

int fila(vector<Fecha> orden, vector<int> &enojados)
{
	int personas = orden.size();
	vector<pair<int, int>> enojos;
	enojos.resize(personas);
	
	int i, j, k;
	int start = personas - 1;
	for(i = 0; i < personas; i++) {
		// i: a quien hago enojar?
		
		// a todo j que
		for(j = start; j > i; j--){
			// tenga menor edad que yo
			if(orden[i] > orden[j]){
				enojos[j].first = max(enojos[j].first, j - i);
				if(j == start)
					start--;
			}
		}
		enojos[i].second = i;
	}
	
	sort(enojos.begin(), enojos.end(), [](const pair<int, int>& a, const pair<int, int>& b){
		if(a.first != b.first)
			return a.first > b.first;
		else
			return a.second < b.second;
	});
	
	i = 0;
	for(const pair<int, int>& kv : enojos){
		if(kv.first == 0)
			break;
		enojados.push_back(kv.second + 1);
	}
	
	if(enojos.size() > 0)
    	return enojos[0].first;
    else
    	return 0;
}
