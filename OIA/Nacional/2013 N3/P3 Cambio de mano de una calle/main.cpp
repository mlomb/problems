#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>

using namespace std;

const int inf = 1 << 30;

int dijkstra(int start, int end, vector< vector<int> > connections) {
	int nodes = connections.size();
	vector<int> dist(nodes);
	vector<int> visited(nodes);
	
	for (int i = 0; i < nodes; ++i)
			dist[i] = inf;
	dist[start] = 0;
	
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
			if (spath < dist[y])
				dist[y] = spath;
		}
	}
	
	return dist[end];
}

int main(){
	int E, start, end, C;
	ifstream file("invertir.in");
	file >> E >> start >> end >> C;
	start--;
	end--;
	vector< vector<int> > connections = vector< vector<int> >(E, vector<int>(E));
	
	for (int i = 0; i < E; i++)
		for (int j = 0; j < E; j++)
			connections[i][j] = inf;
	
	int x, y, weight;
	for(int i = 0; i < C; i++){
		file >> x >> y >> weight;
		connections[x - 1][y - 1] = weight;
	}
	
	int shortest = dijkstra(start, end, connections);
	int modshortest = inf;
	int modnum = -1;
	
	int temp;
	//int s = 0;
	for(int i = 0; i < E * E; i++){
		int x = i / E;
		int y = i % E;
		
		//cout << (s++) << " / "<< (E * E) << endl;
		
		if(connections[x][y] == 0 || connections[y][x] == 0)
			continue;
		
		temp = connections[x][y];
		connections[x][y] = connections[y][x];
		connections[y][x] = temp;
		
		int n = dijkstra(start, end, connections);
		
		temp = connections[y][x];
		connections[y][x] = connections[x][y];
		connections[x][y] = temp;
		
		if(n < modshortest && n > 0) {
			modshortest = n;
			//modnum = i %  + 1;
		}
	}
	
	cout << shortest << endl;
	cout << modshortest << endl;
	cout << modnum << endl;
	
	return 0;
}



