#include <iostream>
#include <deque>
#include <fstream>
#include <math.h>

using namespace std;

const int MAX_N = 1000 + 10;

int points[MAX_N][2];

int main() {
	ifstream cin("norusa.in");
#ifndef LOCAL
	ofstream cout("norusa.out");
#endif
	
	int N;
	cin >> N;
	
	for(int i = 0; i < N; i++)
		cin >> points[i][0] >> points[i][1];
	
	int X, Y;
	cin >> X >> Y;

	int i = 0;
	
	while(X >= points[i][0])
		i++;
	
	int hills = 0;
	double current_speed = 0;
	for(; i < N; i++){
		current_speed += Y - points[i][1];
		
		X = points[i][0];
		Y = points[i][1];
		
		if(current_speed < 0) break;
		if(i % 2 == 0) hills++;
	}
	
	cout << hills << endl;
	
	return 0;
}
