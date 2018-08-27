#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <math.h>

using namespace std;

typedef long double ld;

struct Vec2 {
	ld x, y;
	
	void normalize() {
		ld length = sqrt(x*x + y*y);
		
		if(length == 0)
			return;
		
		x /= length;
		y /= length;
	}
	
	void print() {
		cout << setprecision(12) << fixed << x << " " << y << endl;
	}
	
	void rotate(double angle) {
		ld nx = cos(angle) * x - sin(angle) * y;
		ld ny = cos(angle) * y + sin(angle) * x;
		
		x = nx;
		y = ny;
	}
	
	void add(const Vec2& o) {
		x += o.x;
		y += o.y;
	}
};

int main() {
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	Vec2 p;
	Vec2 v;
	ld a, b, c, d;
	
	cin >> p.x >> p.y;
	cin >> v.x >> v.y;
	cin >> a >> b >> c >> d;
	
	v.x = -v.x;
	v.normalize();
	
	ld angle = atan2l(v.x, v.y);
	
	vector<Vec2> points = {
		{      0, b },
		
		{ -a/2.0, 0 },
		
		{ -c/2.0, 0 },
		{ -c/2.0, -d },
		{  c/2.0, -d },
		{  c/2.0, 0 },
		
		{  a/2.0, 0 },
	};
	
	for(Vec2 pp : points) {
		pp.rotate(angle);
		pp.add(p);
		pp.print();
	}
	
	return 0;
}