#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>
 
using namespace std;
 
int gr_in[30];
int gr_out[30];
 
// union find
int p[30];
 
int padre(int a) {
	if(p[a] == a) {
		return a;
	}
	return padre(p[a]);
}
 
void combinar(int a, int b) {
	int padreA = padre(a);
	int padreB = padre(b);
	if(padreA != padreB) {
		p[padreA] = padreB;
	}
}
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
#ifdef LOCAL
	ifstream cin("words1.in");
#endif
 
	int T, N;
	string word;
	
	cin >> T;
	for(int i = 0; i < T; i++) {
		cin >> N;
		
		for(int j = 0; j < 30; j++) {
			gr_in[j] = 0;
			gr_out[j] = 0;
			p[j] = j;
		}
		
		for(int j = 0; j < N; j++) {
			cin >> word;
			
			int a = word[0] - 'a';
			int b = word[word.length() - 1] - 'a';
			
			gr_out[a]++;
			gr_in[b]++;
			
			combinar(a, b);
		}
		
		bool open = true;
		bool m1 = false, p1 = false; // -1, +1
		bool debilmente_conexa = false;
 
		for(int j = 0; j < 30; j++) {
			//cout << (char)(j+'a') << ": " <<  gr_in[j] << " / " << gr_out[j] << endl;
			int diff = gr_out[j] - gr_in[j];
			if(diff != 0) {
				if(diff == -1 && !m1) {
					m1 = true;
					continue;
				}
				if(diff == 1 && !p1) {
					p1 = true;
					continue;
				}
				open = false;
				break;
			}
		}
		
		if(open) {
			// tiene que ser debilmente conexa
			debilmente_conexa = true;
			
			int main_comp = -1;
			for(int j = 0; j < 30; j++) {
				if(gr_in[j] > 0 || gr_out[j] > 0) {
					int comp = padre(j);
					if(main_comp != comp) {
						if(main_comp == -1)
							main_comp = comp;
						else {
							debilmente_conexa = false;
							break;
						}
					}
				}
			}
		}
		
		if(open && debilmente_conexa) {
			cout << "Ordering is possible." << endl;
		} else {
			cout << "The door cannot be opened." << endl;
		}
	}
	
	return 0;
}
