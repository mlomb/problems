#include <iostream>
#include <fstream>

using namespace std;

struct Point {
	int x, y;
};
struct Rect {
	Point tl, br;
};

pair<int, int> isect(int a1, int a2, int b1, int b2) {
	return make_pair(max(a1, b1), min(a2, b2));
}

int main() {
    ifstream cin("maniobra.in");
#ifndef LOCAL
    ofstream cout("maniobra.out");
#endif
    
    Rect r1, r2;
    
    cin >> r1.br.y >> r1.br.x >> r1.tl.y >> r1.tl.x;
    cin >> r2.br.y >> r2.br.x >> r2.tl.y >> r2.tl.x;

	auto x = isect(r1.tl.x, r1.br.x, r2.tl.x, r2.br.x);
	auto y = isect(r2.br.y, r2.tl.y, r1.tl.y, r1.br.y);
	
	
	cout << x.first << ", " << x.second << endl;
	cout << y.first << ", " << y.second << endl;
	
	
	if(x.second > x.first && y.second > y.first) {
		int sup = (x.second - x.first + 1) * (y.second - y.first + 1);
		cout << sup << endl;
	} else {
		cout << 0 << endl;
	}
	
	return 0;
}
