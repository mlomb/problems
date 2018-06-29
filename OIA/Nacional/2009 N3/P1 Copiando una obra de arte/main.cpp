#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Cell {
	bool R, Z, A;
};

bool valid(Cell** map, char fc, char color, int fc_n, int start, int end){
	bool valid = true;
	
	//cout << fc << " " << color << " " << fc_n << " " << start << " " << end << endl;
	
	for(int j = start; j < end + 1; j++){
		//cout << "test: " << j << endl;
		Cell& cell = fc == 'F' ? map[fc_n][j] : map[j][fc_n];
		if((color == 'R' && !cell.R) ||
		   (color == 'Z' && !cell.Z) ||
		   (color == 'A' && !cell.A)) {
			valid = false;
			//cout << "NOT VALID " << j << endl;
			break;
		}
	}
	
	return valid;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	ifstream fin("copia.in");
	int T;
	fin >> T;
	
	Cell** map = new Cell*[T];
	for(int i = 0; i < T; i++){
		map[i] = new Cell[T];
		for(int j = 0; j < T; j++)
			map[i][j] = Cell();
	}
	
	char fc, color;
	int fc_n, start, end;
	
	int p0;
	fin >> p0;
	for(int i = 0; i < p0; i++){
		fin >> fc >> fc_n >> color >> start >> end;
		fc_n--;
		start--;
		end--;
		for(int j = start; j < end + 1; j++){
			Cell& cell = fc == 'F' ? map[fc_n][j] : map[j][fc_n];
			switch(color){
				case 'R': cell.R = true; break;
				case 'Z': cell.Z = true; break;
				case 'A': cell.A = true; break;
			}
		}
	}
	
	
	int p1;
	fin >> p1;
	int i;
	bool validA = true, validB = true, validC = true, validD = true;
	for(i = 0; i < p1; i++){
		fin >> fc >> fc_n >> color >> start >> end;
		fc_n--;
		start--;
		end--;
		
		validA &= valid(map, fc, color, fc_n, start, end);
		validB &= valid(map, fc == 'F' ? 'C' : 'F', color, fc_n, start, end);
		
		validC &= valid(map, fc, color, T - fc_n - 1, start, end);
		validD &= valid(map, fc == 'F' ? 'C' : 'F', color, T - fc_n - 1, start, end);
		
		if(!validA && !validB && !validC && !validD)
			break;
	}
	
	ofstream fout("copia.out");
	
	fout << i << "\n";
	
	return 0;
}
