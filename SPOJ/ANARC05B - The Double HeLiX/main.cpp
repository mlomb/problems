#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits.h>

#define DB(x) cout << #x << ": " << x << endl;

using namespace std;

int continueSum(vector<int>& v, int& position, int stop){
	int sum = 0;
	for(; position < v.size(); position++){
		int num = v[position];
		sum += num;
		if(num == stop)
			break;
	}
	position++;
	return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
	//fstream cin("input.in");
	
	int N1, N2;
	vector<int> S1, S2;
	
	while(true){
		// S1
		cin >> N1;
		if(N1 == 0) break;
		S1.resize(N1);
		for(int i = 0; i < N1; i++)
			cin >> S1[i];
		
		// S2
		cin >> N2;
		S2.resize(N2);
		for(int i = 0; i < N2; i++)
			cin >> S2[i];
		
		vector<int> intersections;
		set_intersection(S1.begin(), S1.end(), S2.begin(), S2.end(), back_inserter(intersections));
		intersections.push_back(-INT_MAX);
		
		int a = 0, b = 0;
		int sum = 0;
		
		for(int i = 0; i < intersections.size(); i++){
			int point = intersections[i];
			int sum_a = continueSum(S1, a, point);
			int sum_b = continueSum(S2, b, point);
			
			//DB(sum_a)
			//DB(sum_b)
			
			if(sum_a > sum_b)
				sum += sum_a;
			else
				sum += sum_b;
		}
		
		cout << sum << endl;
	}
	
	return 0;
}
