#include <iostream>
#include <string>

using namespace std;

void caminito(string &baldosas)
{
	// B, G, N
	for(int i = 0; i < baldosas.length(); i++){
		if(baldosas[i] == 'R'){
			bool b = true, g = true, n = true;
			
			if((i && baldosas[i - 1] == 'B') || baldosas[i + 1] == 'B') b = false;
			if((i && baldosas[i - 1] == 'G') || baldosas[i + 1] == 'G') g = false;
			if((i && baldosas[i - 1] == 'N') || baldosas[i + 1] == 'N') n = false;
			
			char c;
			if(b) c = 'B';
			if(g) c = 'G';
			if(n) c = 'N';
			
			baldosas[i] = c;
		}
	}
}

