#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <set>
#include <math.h>

using namespace std;

struct Point {
	int x, y;
};

struct Edge {
	int A;
	int B;
	int D2;
};

int S, P;
vector<Point> coords;
vector<Edge> edges;

// union find
int p[500 + 10];

int padre(int a) {
	if(p[a] == a) {
		return a;
	}
	return padre(p[a]);
}

void combinar(int a, int b) {
	int padreA = padre(a);
	int padreB = padre(b);
	if(padreA != padreB) {
		p[padreA] = padreB;
	}
}

bool test(int D2) {
	for(int i = 0; i < P; i++) {
		p[i] = i;
	}
	
	// MST
	for(int i = 0; i < int(edges.size()); i++) {
		if(D2 < edges[i].D2)
			break;
		
		combinar(edges[i].A, edges[i].B);
	}
	
	set<int> s;
	for(int i = 0; i < P; i++) {
		s.insert(p[i]);
	}
	
	// cuantas islas quedan?
	// return cant <= S
	// cosmico
	return int(s.size()) <= S;
}

int main() {
	fstream cin("artic_network.in");
	
	int cases;
	cin >> cases;
	
	for(int i = 0; i < cases; i++) {
		cin >> S >> P;
		coords.resize(P);
		edges.clear();
		
		for(int j = 0; j < P; j++)
			cin >> coords[j].x >> coords[j].y;
		
		for(int j = 0; j < P; j++) {
			for(int k = j + 1; k < P; k++) {
				Edge e;
				e.A = j;
				e.B = k;
				
				int dx = (coords[j].x - coords[k].x);
				int dy = (coords[j].y - coords[k].y);
				
				e.D2 = dx * dx + dy * dy;
				
				edges.push_back(e);
			}
		}
		
		sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
			return a.D2 < b.D2;
		});
		
		int l = 0, r = 200000000 + 10;
		while(l<r-1) {
			int mid = (l + r) / 2;
			
			if(test(mid))
				r = mid;
			else
				l = mid;
		}
		
		cout << setprecision(2) << fixed << sqrt(l) << endl;
	}
	
	return 0;
}
