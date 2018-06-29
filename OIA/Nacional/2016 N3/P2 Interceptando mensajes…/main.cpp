#include <iostream>
#include <string>

using namespace std;

bool tryToDecipher(char passcodeA, char passcodeB, string& captado, string& conocido, string& result){
	int coincidence = 0;
	bool swapper = false, found = false;
	result.clear();

	for(int i = 0; i < captado.length(); i++){
		char offset = 0;
		if(swapper)
			offset = passcodeB - 'A';
		else
			offset = passcodeA - 'A';
		swapper = !swapper;
		
		char c = (char)((captado[i] - 'A' + offset) % 26 + 'A');

		if (!found && conocido[coincidence] == c) {
			coincidence++;
			if (coincidence == conocido.length())
				found = true;
		}
		else
			coincidence = 0;

		result.push_back(c);
	}

	if (found)
		cout << result << endl;

	return found;
}

void desvela(string& captado, string& conocido) {	
	string norm_conocido = "", result = "";
	
	for (int i = 0; i < conocido.length(); i++) {
		char c = conocido[i];
		if (c != '*' && c != ' ')
			norm_conocido.push_back(c);
	}

	for(char i = 'A'; i < 'Z' + 1; i++){
		for(char j = 'A'; j < 'Z' + 1; j++){
			if (tryToDecipher(i, j, captado, norm_conocido, result))
				return;
		}
	}

	cout << "No encontrado." << endl;
}

int main(){
	string captado = "ARJHNRIUCGQHPFGQFHTXPDEHTLNOC";
	string conocido = "DER UNA *";
	
	desvela(captado, conocido);
	
	return 0;
}
