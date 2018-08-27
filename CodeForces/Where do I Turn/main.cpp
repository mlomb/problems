#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

typedef long long int lli;
const lli INF = 9999999999;

int main() {
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	lli ax, ay;
	lli bx, by;
	lli cx, cy;
	
	cin >> ax >> ay;
	cin >> bx >> by;
	cin >> cx >> cy;
	
	lli x1 = bx - ax;
	lli y1 = by - ay;
	
	lli x2 = cx - bx;
	lli y2 = cy - by;
	
	lli a = x1 * y2;
	lli b = x2 * y1;
	
	if(a == b)
		cout << "TOWARDS" << endl;
	else
		cout << (a > b ? "LEFT" : "RIGHT") << endl;
	
	return 0;
}