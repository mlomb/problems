#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int distanceFromCenter(int x, int y, int cx, int cy){
	return abs(x - cx) + abs(y - cy);
}

bool isOutside(int x, int y, int cx, int cy, int max) {
	return abs(x - cx) > max || abs(y - cy) > max;
}

bool cellVerify(vector< vector<int> >& map, int x, int y, int cx, int cy, int d, int value, int k) {
	if (isOutside(x, y, cx, cy, k))
		return true;
	if (distanceFromCenter(x, y, cx, cy) > d)
		if (map[x][y] >= value)
			return false;
	return true;
}

bool isCellValid(vector< vector<int> >& map, int x, int y, int cx, int cy, int k) {
	if (isOutside(x, y, cx, cy, k))
		return true;
	int value = map[x][y];
	int d = distanceFromCenter(x, y, cx, cy);

	return cellVerify(map, x, y + 1, cx, cy, d, value, k) &&
		   cellVerify(map, x, y - 1, cx, cy, d, value, k) &&
		   cellVerify(map, x + 1, y, cx, cy, d, value, k) &&
		   cellVerify(map, x - 1, y, cx, cy, d, value, k);
}

void lomas(vector< vector<int> >& map, int m, int n, int k) {
	short maxX = n - k;
	short maxY = m - k;
	
	for(int y = k; y < maxY; y++){
		for(int x = k; x < maxX; x++){
			bool valid = true;

			for (int yy = y - k; yy < y + k && valid; yy++) {
				for (int xx = x - k; xx < x + k && valid; xx++) {
					valid &= isCellValid(map, xx, yy, x, y, k);
				}
			}
			
			if(valid)
				cout << "Loma posible en: (" << (x + 1) << ", " << (y + 1) << ")" << endl;
		}
	}
}

int main(){
	int m;
	int n;
	int k;

	ifstream f("lomas2.in");
	f >> m;
	f >> n;
	f >> k;

	vector< vector<int> > map = vector< vector<int> >(n, vector<int>(m));

	for (int y = 0; y < m; y++) {
		for (int x = 0; x < n; x++) {
			f >> map[x][y];
		}
	}
	
	/*
	for(int y = 0; y < m; y++){
		for(int x = 0; x < n; x++){
			cout << map[x][y];
		}
		cout << endl;
	}
	*/
	
	lomas(map, m, n, k);
	
	return 0;
}