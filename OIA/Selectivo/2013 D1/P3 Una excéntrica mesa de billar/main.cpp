#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

/*
	Este es un problema largo y aburrido
	No se lo recomiendo a nadie
	;)
*/

static int orden_id = 1;

struct Line {
	int x1, y1;
	int x2, y2;
};

struct Casilla {
	//   | \     /
	//   |  \  / 
	//   |   \/
	//   |   /\
	//   |  /  \
	//   |/_____\
	
	// 0 = no existe, sino ID (para el orden de entrada)
	int left, bottom;
	int diag1, diag2; // diag1 = /
	
	// direccion
	bool dLeft, dBottom;
	bool dDiag1, dDiag2;
};

Casilla mapa[1005][1005];
std::map<int, Line> resultado;

void connect(int x1, int y1, int x2, int y2) {
	int dx = x2 - x1;
	int dy = y2 - y1;
		
	int movs = max(abs(dx), abs(dy));
	
	int ddx = dx / movs;
	int ddy = dy / movs;
	
	int addx = abs(ddx);
	int addy = abs(ddy);
	
	if(dx < 0)
		x1 += ddx;
	if(dy < 0)
		y1 += ddy;
	
	//cout << "------------" << endl;
	
	for(int k = 0; k < movs; k++){
		int fx = x1 + ddx * k;
		int fy = y1 + ddy * k;
		
		//cout << fx << ", " << fy << ": ";
		if((ddx == 1 && ddy == 1) || (ddx == -1 && ddy == -1)){
			mapa[fx][fy].diag1 = orden_id++;
			mapa[fx][fy].dDiag1 = x1 < x2;
			//cout << "Diag 1" << endl;
		} else if((ddx == -1 && ddy == 1) || (ddx == 1 && ddy == -1)){
			mapa[fx][fy].diag2 = orden_id++;
			mapa[fx][fy].dDiag2 = x1 < x2;
			//cout << "Diag 2" << endl;
		} else if(addx == 1){
			mapa[fx][fy].bottom = orden_id++;
			mapa[fx][fy].dBottom = ddx > 0;
			//cout << "Bottom" << endl;
		} else if(addy == 1) {
			mapa[fx][fy].left = orden_id++;
			mapa[fx][fy].dLeft = ddy > 0;
			//cout << "Left" << endl;
		}
		
	}
}

// retorna true si ya existia el resultado
bool addToResult(int id, Line line) {
	auto it = resultado.find(id);
	if(it != resultado.end())
		return true;
	else
		resultado.insert(make_pair(id, line));
	return false;
}

void addLeftToResult(int x, int y){
	Line l;
	if(mapa[x][y].dLeft)
		l = { x, y, x, y + 1 };
	else
		l = { x, y + 1, x, y };
	addToResult(mapa[x][y].left, l);
}

void addBottomToResult(int x, int y){
	Line l;
	if(mapa[x][y].dBottom)
		l = { x, y, x + 1, y };
	else
		l = { x + 1, y, x, y };
	addToResult(mapa[x][y].bottom, l);
}

void raycast2d(int x, int y, int dx, int dy) {
	if(x < 0 || y < 0 || x > 1004 || y > 1004)
		return;
	//cout << x << ", " << y << " D " << dx << ", " << dy << endl;
	
	int adx = abs(dx);
	int ady = abs(dy);
	
	if(mapa[x][y].diag1){
		Line l;
		if(mapa[x][y].dDiag1)
			l = { x, y, x + 1, y + 1 };
		else
			l = { x + 1, y + 1, x, y };
		if(addToResult(mapa[x][y].diag1, l))
			return;
		
		if(dy == -1 && mapa[x][y].left){
			addLeftToResult(x, y);
			return;
		}
		if(dx == -1 && mapa[x][y].bottom){
			addBottomToResult(x, y);
			return;
		}
		
		swap(dx, dy);
		
	} else if(mapa[x][y].diag2){
		Line l;
		if(mapa[x][y].dDiag2)
			l = { x, y + 1, x + 1, y };
		else
			l =  { x + 1, y, x, y + 1 };
		if(addToResult(mapa[x][y].diag2, l))
			return;
			
		if(dy == 1 && mapa[x][y].left){
			addLeftToResult(x, y);
			return;
		}
		if(dx == 1 && mapa[x][y].bottom){
			addBottomToResult(x, y);
			return;
		}
		
		swap(dx, dy);
		dx = -dx;
		dy = -dy;
	} else {
		if(adx == 0 && ady == 1){
			if(mapa[x][y].bottom){
				addBottomToResult(x, y);
				return;
			}
		}
		if(ady == 0 && adx == 1){
			if(mapa[x][y].left){
				addLeftToResult(x, y);
				return;
			}
		}
	}
	
	raycast2d(x + dx, y + dy, dx, dy);
}

int main() {
	ifstream fin("billar.in");
	ofstream fout("billar.out");
	
	int N;
	fin >> N;
	
	// Crear el mapa
	int x, y, lastX, lastY, sx, sy;
	fin >> lastX >> lastY;
	sx = lastX, sy = lastY;
	for(int i = 0; i < N - 1; i++){
		fin >> x >> y;
		
		connect(lastX, lastY, x, y);
		
		lastX = x;
		lastY = y;
	}
	connect(lastX, lastY, sx, sy);
	
	// Hacer el raycast
	int x1, y1, x2, y2;
	fin >> x1 >> y1 >> x2 >> y2;
	
	// up down
	for(int i = x1; i < x2; i++){
		raycast2d(i, y1, 0, 1);
		raycast2d(i, y1, 0, -1);
	}
	// right left
	for(int j = y1; j < y2; j++){
		raycast2d(x1, j, 1, 0);
		raycast2d(x1, j, -1, 0);
	}
	
	// Unir las lineas
	vector<Line> resultadoUnido;
	auto it = resultado.begin();
	Line lastLine = (*it).second;
	int cdx = lastLine.x2 - lastLine.x1, cdy = lastLine.y2 - lastLine.y1;
	it++;
	for(; it != resultado.end(); it++){
		Line l = (*it).second;
		int dx = l.x2 - l.x1;
		int dy = l.y2 - l.y1;
		//cout << l.x1 << " " << l.y1 << " " << l.x2 << " " << l.y2 << " D " << dx << ", " << dy << endl;
		if(lastLine.x2 == l.x1 && lastLine.y2 == l.y1 && cdx == dx && cdy == dy){
			// la linea tiene el mismo delta y estan pegadas
			lastLine.x2 = l.x2;
			lastLine.y2 = l.y2;
		} else {
			resultadoUnido.push_back(lastLine);
			lastLine = l;
			cdx = dx;
			cdy = dy;
		}
	}
	resultadoUnido.push_back(lastLine);
	
	// Mostrar el resultado
	for(Line& l : resultadoUnido)
		fout << l.x1 << " " << l.y1 << " " << l.x2 << " " << l.y2 << endl;
	
	/*
	// Debug
	for(auto& l : resultado)
		cout << l.second.x1 << " " << l.second.y1 << " " << l.second.x2 << " " << l.second.y2 << endl;
	*/
	
	resultado.clear();
	
	return 0;
}
