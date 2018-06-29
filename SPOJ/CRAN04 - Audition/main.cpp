#include <iostream>
#include <fstream>
#include <string>
#include <deque>

typedef long long int lli;

using namespace std;

int main(){
	fstream cin("input.in");
	
	int T;
	cin >> T;
	
	for(int i = 0; i < T; i++){
		lli N, K;
		string line;
		cin >> N >> K >> line;
		
		/*
		lli pos = 0;
		deque<lli> dq;
		for(char c : line) {
			bool boy = c == '1';
			
			if(boy) dq.push_back(pos);
			pos++;
		}
		*/
		
		lli sum = 0, subsum = 0;
		int a = 0, b = 0;
		while(a < N && b < N) {
			
			// advance b
			while(b < N) {
				b++;
				if(line[b] == '1') subsum++;
				if(subsum == K){
					sum++;
					break;
				}
			}
			
			// advance a
			
			/*
			if(subsum == K) {
				sum++;
				
				// advance a
				if(line[a] == '1') subsum--;
				a++;
			} else {
				// advance b
				b++;
				if(line[b] == '1') subsum++;
			}
			*/
			cout << sum << endl;
		}
		
	}
	
	return 0;
}
