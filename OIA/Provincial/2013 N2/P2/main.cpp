#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <windows.h>

using namespace std;

const int inf = 1 << 30;// Infinito

vector<int> dijkstra(int start, int end, vector< vector<int> > connections) {
	int nodes = connections.size();
	vector< vector<int> > path(nodes);
	vector<int> dist(nodes);
	vector<int> visited(nodes);

	for (int i = 0; i < nodes; ++i) {
		dist[i] = inf;
		path[i] = vector<int>();
	}
	dist[start] = 0;

	/* Dijkstra */
	for (int x = 0; x < nodes; ++x) {
		int current = -1;
		for (int y = 0; y < nodes; ++y) {
			if (visited[y]) continue;
			if (current == -1 || dist[y] < dist[current])
				current = y;
		}

		visited[current] = true;
		for (int y = 0; y < nodes; ++y) {
			int spath = dist[current] + connections[current][y];
			if (spath < dist[y]) {
				dist[y] = spath;
				path[y] = path[current];
				path[y].push_back(current);
			}
		}
	}
	//path[end].push_back(end);

	return path[end];
}

struct Monster {
	int x, y;
	int radius;
};

bool isInAttack(int x, int y, vector<Monster> monsters) {
	for (int j = 0; j < monsters.size(); j++) {
		Monster m = monsters[j];
		int delta = abs(x - m.x) + abs(y - m.y);
		if (delta <= m.radius)
			return true;
	}
	return false;
}

bool isNumber(char c) {
	return c > 48 && c < 58;
}

int main() {
	int w, h; // Ancho y alto del mapa
	int e, s; // Los índices de los nodos de entrada y salida

	ifstream file("mapBig.txt");
	file >> h >> w;
	cout << w << "x" << h << endl;

	vector< vector<char> > charMap(h);
	vector< vector<int> > map(h);
	vector<Monster> monsters;
	int nodes = w * h + 1;
	int i = 0;
	char n;

	for (int y = 0; y < h; ++y) {
		charMap[y] = vector<char>(w);
		map[y] = vector<int>(w);
		for (int x = 0; x < w; ++x) {
			file >> n;
			if (isNumber(n)) {
				Monster m = { x, y, n - 48 };
				monsters.push_back(m);
			}
			charMap[y][x] = n;
		}
	}
	file.close();

	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			n = charMap[y][x];
			map[y][x] = -1;

			if (n == 'S')
				s = i;
			else if (n == 'E')
				e = i;

			if (n == '#' || isNumber(n) || isInAttack(x, y, monsters))
				nodes--;
			else {
				map[y][x] = i;
				i++;
			}
		}
	}

	vector< vector<int> > connections(nodes);
	for (int i = 0; i < nodes; ++i) {
		connections[i] = vector<int>(nodes);
		for (int j = 0; j < nodes; ++j) {
			connections[i][j] = inf;
		}
	}

	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			if (map[y][x] < 0)
				continue;
			if (y > 0 && map[y - 1][x] >= 0) {
				connections[map[y][x]][map[y - 1][x]] = 1;
				connections[map[y - 1][x]][map[y][x]] = 1;
			}
			if (y < h - 1 && map[y + 1][x] >= 0) {
				connections[map[y][x]][map[y + 1][x]] = 1;
				connections[map[y + 1][x]][map[y][x]] = 1;
			}
			if (x > 0 && map[y][x - 1] >= 0) {
				connections[map[y][x]][map[y][x - 1]] = 1;
				connections[map[y][x - 1]][map[y][x]] = 1;
			}
			if (x < w - 1 && map[y][x + 1] >= 0) {
				connections[map[y][x]][map[y][x + 1]] = 1;
				connections[map[y][x + 1]][map[y][x]] = 1;
			}
		}
	}

	/*
		Esto es cualquiera, pero como el dijkstra que usamos
		no acepta tener nodos aislados o grafos aislados,
		tengo que unir todos los nodos para que no crashee,
		los uno con un nodo fantasma con una distancia a
		todos los demás nodos que sea imposible de alcanzar (w*h)
		entonces todos están conectados.
		Y en caso de que no haya camino, si el camino que se devuelve
		contiene este nodo (con indice nodes - 1) verificamos que no
		hay un camino posible.
	*/
	int impossible = w * h;
	for (int x = 0; x < nodes; ++x) {
		connections[x][nodes - 1] = impossible;
		connections[nodes - 1][x] = impossible;
	}
		
	/* Path */
	vector<int> path = dijkstra(e, s, connections);
	
	if(find(path.begin(), path.end(), nodes - 1) != path.end()){
		cout << "No possible path." << endl << "-1" << endl;
		return -1;
	}

	/* Camino mas corto */
	cout << "Found a path in " << path.size() << " move(s)." << endl;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Para cambiar los colores

	cout << "Path:" << endl;
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			bool inAttack = isInAttack(x, y, monsters);

			SetConsoleTextAttribute(hConsole, 13);
			if (charMap[y][x] == '#') {
				SetConsoleTextAttribute(hConsole, 15);
				if (inAttack)
					SetConsoleTextAttribute(hConsole, 12);
				cout << "#";
			}
			else if (map[y][x] == e)
				cout << "E";
			else if (map[y][x] == s)
				cout << "S";
			else if (find(path.begin(), path.end(), map[y][x]) != path.end()) {
				SetConsoleTextAttribute(hConsole, 10);
				cout << "X";
			}
			else if (charMap[y][x] != '.') {
				SetConsoleTextAttribute(hConsole, 9);
				cout << "M";
			}
			else {
				SetConsoleTextAttribute(hConsole, 11);
				if (inAttack)
					SetConsoleTextAttribute(hConsole, 12);
				cout << ".";
			}
			//cout << " "; Habilitar en caso de querer verlo espaciado
		}
		cout << endl;
	}
	SetConsoleTextAttribute(hConsole, 7); // Color de consola normal

	system("PAUSE");
	return path.size();
}
