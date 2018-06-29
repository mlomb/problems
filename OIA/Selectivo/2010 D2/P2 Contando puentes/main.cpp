#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Line {
	int x, y;
	int delta;
};

void addPoint(int x1, int y1, int x2, int y2, vector<Line>& horz, vector<Line>& vert){
	if(x1 == x2) // vert
		vert.emplace_back(Line { x1, min(y1, y2), abs(y1 - y2) });
	else // horz
		horz.emplace_back(Line { min(x1, x2), y1, abs(x1 - x2) });
}

void load(ifstream& cin, vector<Line>& horz, vector<Line>& vert) {
	int M;
	cin >> M;
	
	horz.reserve(M / 2);
	vert.reserve(M / 2);
	
	int x, y;
	int last_x, last_y;
	int first_x, first_y;
	
	cin >> last_x >> last_y;
	first_x = last_x, first_y = last_y;
	
	for(int i = 0; i < M - 1; i++){
		cin >> x >> y;
		addPoint(last_x, last_y, x, y, horz, vert);
		last_x = x;
		last_y = y;
	}
	
	addPoint(last_x, last_y, first_x, first_y, horz, vert);
}

bool does_cross(const Line& lh, const Line& lv){
	return lv.x > lh.x && lv.x < lh.x + lh.delta &&
		   lh.y > lv.y && lh.y < lv.y + lv.delta;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	ifstream cin("autodromo.in");
	
	vector<Line> horz_A, vert_A, horz_B, vert_B;
	
	load(cin, horz_A, vert_A);
	load(cin, horz_B, vert_B);
	
	int cruces = 0;
	
	for(const Line& lh : horz_A){
		for(const Line& lv : vert_B){
			if(does_cross(lh, lv)){
				cruces++;
			}
		}
	}
	for(const Line& lh : horz_B){
		for(const Line& lv : vert_A){
			if(does_cross(lh, lv)){
				cruces++;
			}
		}
	}
	
	ofstream fout("autodromo.out");
	fout << cruces << endl;
	
	return 0;
}

