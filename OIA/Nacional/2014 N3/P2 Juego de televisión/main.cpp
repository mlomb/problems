#include <iostream>

using namespace std;

void recurse(const int current, int& wins, int& maxPrizeTimes, int& maxPrize, int prize, int mov, const int S, const int M, const int* acierto, const int* error, const int* cupon, const int* fin, bool right){
	if(mov == M - 1){
		for(int i = 0; i < S; i++){
			if(current == fin[i] - 1){
				if(prize > maxPrize){
					maxPrize = prize;
					maxPrizeTimes = 0;
				}
				if(prize == maxPrize)
					maxPrizeTimes++;
				wins++;
				break;
			}
		}
		return;
	}
	
	mov++;
	if(right)
		prize += cupon[current];
	
	recurse(acierto[current] - 1, wins, maxPrizeTimes, maxPrize, prize, mov, S, M, acierto, error, cupon, fin, true);
	recurse(error[current]   - 1, wins, maxPrizeTimes, maxPrize, prize, mov, S, M, acierto, error, cupon, fin, false);
}

void TV( int C, int S, int M, int acierto[], int error[],int cupon[],int fin[], int * ng, int * maxp, int * nmaxp ){
	recurse(0, *ng, *nmaxp, *maxp, 0, 0, S, M, acierto, error, cupon, fin, false);
}

int main(){
	int acierto[] = { 2, 5,  5, 4,  5 };
	int error[]   = { 4, 3,  1, 4,  2 };
	int cupon[]   = { 5, 10, 7, 20, 8 };
	int fin[] = { 3 };
	
	int ng, maxp, nmaxp;
	
	TV(5, 1, 6, acierto, error, cupon, fin, &ng, &maxp, &nmaxp);
	
	cout << ng << " " << maxp << " " << nmaxp << endl;
		
	return 0;
}
