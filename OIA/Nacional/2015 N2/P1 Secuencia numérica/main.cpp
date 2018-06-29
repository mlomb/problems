#include <iostream>
using namespace std;

void secuencia(int s, int l, int* lof, int* p, int* i, int* n){
	int number = s;
	int lastNumber = -s;
	bool status = false;
	int c = 0;
	cout << number << endl;
	
	while(number != 1 && (*lof) < l - 1){
		if(number % 2 == 0){
			number /= 2;
			(*p)++;
		} else {
			number *= 3;
			number++;
			(*i)++;
		}
		bool now = number < lastNumber;
		
		if(status != now){
			if(c > (*n))
				(*n) = c;
			cout << "Seguidilla de " << c << endl;
			c = 0;
			status = true;
		}else if(c == 0 && !now){
			c++;
			status = !status;			
		}
			
		lastNumber = number;
		cout << number << endl;
		(*lof)++;
	}
	if(number == 1){
		(*i)++;
		(*lof)++;
	}else if((*lof) == l - 1){
		(*lof) = number;		
	}
}

int main(){
	int s, l , lof, p, i, n;
	p = 0;
	i = 0;
	lof = 0;
	n = 0;
	
	s = 22;
	l = 100;
	
	secuencia(s, l, &lof, &p, &i, &n);
	cout << p << " pares, " << i << " impares" << endl;
	cout << lof << " lof" << endl;
	cout << n << " seguidillas" << endl;
	return 0;
}
