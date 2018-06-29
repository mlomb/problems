#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream ifile("empaque.in");
	
	int S, count;
	
	ifile >> S >> count;
	
	int current = 0;
	int packages = 0;
	int l, a, e;
	
	for(int i = 0; i < count; i++) {
		ifile >> l >> a >> e;
		int size = l + a + e;
		
		cout << current << endl;
		
		if(current + size >= S){
			packages++;
			current = 0;
			cout << "+1" << endl;
		}
		
		current += size;
	}
	
	
	cout << packages;
	
	return 0;
}
