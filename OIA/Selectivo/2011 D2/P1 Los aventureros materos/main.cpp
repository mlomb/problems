#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

#define LSB(x) (x & (-x))
typedef long long int lli;

lli N;
lli ftree[500000 + 100];

void add(unsigned int index, lli amount) {
	while(index <= N) {
		ftree[index] += amount;
		index += LSB(index);
	}
}

int get(unsigned int index) {
	lli sum = 0;
	while(index > 0) {
		sum += ftree[index];
		index -= LSB(index);
	}
	return sum;
}

unsigned int invert(lli value) {
	unsigned int index = 0;
	unsigned int logmaxn = 1 << ((unsigned int)log2(N) - 1);
	for(unsigned int d = logmaxn;d; d >>= 1){
		if(ftree[index | d] < value){
			index |= d;
			value -= ftree[index];
		}
	}
	return index + 1;
}

/*
lli get_wrapped(unsigned int index){
	lli all = get(N);
	lli times = index / N;
	lli result = get(index % N) + all * times;
	return result;
}
*/

int main() {
	ifstream cin("aventureros.in");
#ifndef LOCAL
	ofstream cout("aventureros.out");
#endif
	
	cin >> N;
	
	for(int i = 0; i < N; i++)
		add(i + 1, 1);
	
	vector<lli> salen;
	salen.resize(N - 1);
	lli cebador = 1;
	lli a;
	for(int i = 0; i < N - 1; i++){
		cin >> a;
		a++;
		
		lli base = get(cebador - 1);
		lli all = get(N);
		
		a = (a - 1) % all + 1; // magic is here
		
		//for(int i = 1; i <= N; i++)
		//	cout << get(i) - get(i - 1) << " ";
		//cout << endl;
		//cout << "a: " << a << " cebador: " << cebador << endl;
		
		cebador = invert(a);
		
		/*
		lli l = cebador - 1;
		lli r = l + N + 1;
		while(r - l > 1) {
			lli mid = (l + r) / 2;
			
			lli times = mid / N;
			lli wrapped = get(mid % N) + all * times;
			lli diff = wrapped - base;
			
			//cout << "r: " << r << ", l: " << l << " mid: " << mid << "       ";
			//cout << cebador << " -> " << mid << "    ";
			//cout << "diff: " << diff << endl;
			
			if(diff < a)
				l = mid;
			else
				r = mid;
		}
		
		cebador = (r - 1) % N + 1;
		*/
		
		add(cebador, -1);
		
		salen[i] = cebador;
	}
	
	for(lli i : salen)
		cout << i << " ";
	cout << "\n";
	
	
	lli l = 0, r = N + 1;
	while(r - l > 1){
		lli mid = (l+r) / 2;
		
		if(get(mid))
			r = mid;
		else
			l = mid;
	}
	cout << r << "\n";
	
	return 0;
}
