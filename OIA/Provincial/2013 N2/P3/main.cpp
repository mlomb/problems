#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
	ifstream file("EJ.txt");
	int questions, max;
	int number;
	
	file >> questions >> max;
	
	cout << "Preguntas: " << questions << endl << "Del 1 al " << max << endl;
	
	while(file >> number){
		int sum = 1;
		int count = 0;
		int jump = 1;
		for(int x = 1; x < number; x++){
			sum += x + 1;
			jump++;
			if(sum == number)
				count++;
			if(sum >= number)
				break;
			/* -- */
			int sumac = sum;
			while(sumac < number){
				sumac += jump;
				if(sumac == number)
					count++;
			}
		}
		cout << number << " -> " << count << endl;
	}
	return 0;
}
