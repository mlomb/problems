#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#else
	freopen("ascii.in", "r", stdin);
	freopen("ascii.out", "w", stdout);
#endif

	
	
	int H, W;
	cin >> H >> W;
	
	int area = 0;
	char c;
	for(int i = 0; i < H; i++) { // y
		bool inside = false;
		for(int j = 0; j < W; j++) { // x
			cin >> c;
			if(c == '/') {
				inside = !inside;
				area++;
			} else if(c == '\\') {
				inside = !inside;
				area++;
			}
			
			if(inside) {
				if(c == '.')
					area += 2;
			}
		}
	}
	
	cout << area/2 << endl;
	
	
	return 0;
}