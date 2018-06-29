#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

bool areBoundsValid(int x, int y, int size){
	return x >= 0 && y >= 0 && x < size && y < size;
}

int maxAPath(int x, int y, int xx, int yy, int size, int m, vector< vector<int> >& barrio, vector< vector<int> >& longest);

int treeLongestPathRec(int x, int y, int size, vector< vector<int> >& barrio, vector< vector<int> >& longest){
	int cached = longest[x][y];
	if(cached >= 0)
		return cached;

	int m = 0;
	
	m = maxAPath(x, y, x, y + 1, size, m, barrio, longest);
	m = maxAPath(x, y, x, y - 1, size, m, barrio, longest);
	m = maxAPath(x, y, x + 1, y, size, m, barrio, longest);
	m = maxAPath(x, y, x - 1, y, size, m, barrio, longest);
	
	m++;
	
	longest[x][y] = m;
	
	return m;
}

int maxAPath(int x, int y, int xx, int yy, int size, int m, vector< vector<int> >& barrio, vector< vector<int> >& longest){
	if(areBoundsValid(xx, yy, size))
		if(barrio[x][y] > barrio[xx][yy])
			m = max(m, treeLongestPathRec(xx, yy, size, barrio, longest));
	return m;
}

bool generatePathCheck(int i, int x, int y, int xx, int yy, int M, vector< vector<int> >& longest, int* xxx, int* yyy, string* recorrido, string dir){
	if(areBoundsValid(xx, yy, M) && longest[xx][yy] == i) {
		*xxx = xx;
		*yyy = yy;
		*recorrido += dir;
		return true;
	}
	return false;
}

string generatePath(int x, int y, int M, vector< vector<int> >& longest, int* sx, int* sy){
	int i = longest[x][y];
	int xx = x;
	int yy = y;
	string recorrido = "";
	
	while(i >= 0){
		bool a = generatePathCheck(i, xx, yy, xx, yy + 1, M, longest, &xx, &yy, &recorrido, "S") ||
				 generatePathCheck(i, xx, yy, xx, yy - 1, M, longest, &xx, &yy, &recorrido, "N") ||
				 generatePathCheck(i, xx, yy, xx + 1, yy, M, longest, &xx, &yy, &recorrido, "E") ||
				 generatePathCheck(i, xx, yy, xx - 1, yy, M, longest, &xx, &yy, &recorrido, "O");
		
		i--;
	}
	
	*sx = xx;
	*sy = yy;

	return recorrido;
}

int karting(vector< vector<int> > barrio, int* pista, string& recorrido){
	pista[0] = 0;
	pista[1] = 0;
	pista[2] = 0;
	pista[3] = 0;
	recorrido = "";
	
	int M = barrio.size();
	vector< vector<int> > longest = vector< vector<int> >(M, vector<int>(M, -1));
	
	int mmax = 0;
	
	for(int y = 0; y < M; y++){
		for(int x = 0; x < M; x++){
			int r = treeLongestPathRec(x, y, M, barrio, longest) - 1;
			if(r > mmax){
				pista[0] = x;
				pista[1] = y;
				mmax = r;
			}
		}
	}
	
	if(mmax > 0) {
		recorrido = generatePath(pista[0], pista[1], M, longest, &pista[2], &pista[3]);
	
		pista[0]++;
		pista[1]++;
		pista[2]++;
		pista[3]++;
	}
	
	return mmax;
}

int main(){
	vector< vector<int> > barrio;
	int pista[2][2];
	string recorrido;
	int M;
	
	ifstream f("karting.in");
	f >> M;
	
	barrio = vector< vector<int> >(M, vector<int>(M, 0));
	
	for(int i = 0; i < M; i++)
		for(int j = 0; j < M; j++)
			f >> barrio[j][i];

	int count = karting(barrio, *pista, recorrido);
	
	cout << "El largo de la pista es " << count << endl;
	cout << "Inicio: (" << pista[0][0] << ", " << pista[0][1] << ") ";
	cout << "Fin: (" << pista[1][0] << ", " << pista[1][1] << ")" << endl;
	cout << recorrido << endl;
	
	return 0;
}

