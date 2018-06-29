#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <math.h>

using namespace std;

int conecta(char cadena[], int pares[]){
	int len = strlen(cadena);
	int parespos = 0;
	for(int jump = 1; jump < len; jump++){
		//cout << jump << endl;
		for(int i = 0; i < len; i++){
			int pos2 = (i + jump) % len;
			int v1 = cadena[i];
			int v2 = cadena[pos2];
			
			//cout << i << ": " << v1 << ", " << pos2 << ": " << v2 << endl;
			if(v1 != v2){
				bool isInFlag = false;
				for(int j = 0; j < parespos; j++){
					if(pares[j] == i || pares[j] == pos2){
						isInFlag = true;
						break;
					}
				}
				if(!isInFlag){
					pares[parespos] = i;
					pares[parespos + 1] = pos2;
					parespos += 2;
					//cout << "Si" << endl;
				}
			}
		}
	}
	return parespos / 2;
}

int main(){
	char* cadena = "LLLLCCCLC";
	int *pares = new int[500]; 
	int result = conecta(cadena, pares);
	
	cout << result << endl;
	for(int i = 0; i < result*2; i+=2){
		cout << (pares[i] + 1) << " " << (pares[i + 1] + 1) << endl;
	}
	
	return 0;
}
