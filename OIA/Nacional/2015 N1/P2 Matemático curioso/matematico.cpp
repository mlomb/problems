#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream input("matematico.in");
	
	int seed;
	input >> seed;
	
	int nums[5000];
	int i = 0, n, max = 0;
	
	nums[0] = seed;
	
	do {
		n = nums[i];
		
		if(n % 2 != 0){
			n *= 3;
			n++;
		} else
			n /= 2;
		i++;
		nums[i] = n;
		
		if(n > max)
			max = n;
	} while(nums[i] > 1);
		
	cout << (i + 1) << endl;
	cout << max << endl;
	
	ofstream output("matematico.out");
	output << (i + 1) << endl;
	output << max << endl;
	
	return 0;
}
