#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

typedef long long int lli;

lli m1(lli r, lli g, lli b) {
	lli count = 0;
	
	count += r/3 + g/3 + b/3;
	r %= 3;
	g %= 3;
	b %= 3;
	
	count += min(r, min(g, b));
	
	return count;
}

lli m2(lli r, lli g, lli b) {
	lli count = 0;
	
	count += min(r, min(g, b));
	r -= count;
	g -= count;
	b -= count;
	count += r/3 + g/3 + b/3;
	
	return count;
}

int main() {
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	lli r, g, b;
	cin >> r >> g >> b;

	int rm = r % 3,
		gm = g % 3,
		bm = b % 3;

	int a = 0;
	if((rm == 0 && gm == 2 && bm == 2 && r > 0) ||
	   (rm == 2 && gm == 0 && bm == 2 && g > 0) ||
	   (rm == 2 && gm == 2 && bm == 0 && b > 0)) {
	   	r -= 2;
	   	g -= 2;
	   	b -= 2;
	   	a = 2;
	}
	
	cout << max(m1(r,g,b), m2(r,g,b)) + a << endl;
	
	return 0;
}