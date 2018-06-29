#include <iostream>
#include <vector>

using namespace std;

int main(){
	int h1, h2, a1, a2, c1;
	cin >> h1 >> a1 >> c1;
	cin >> h2 >> a2;
	
	vector<bool> game;
	
	while(h2 > 0) {
		bool action = true; // strike
		if(h1 - a2 <= 0 && h2 - a1 > 0 /* no me curo si lo mato en este turno */)
			action = false; // heal
		game.push_back(action);
		
		if(action)
			h2 -= a1;
		else
			h1 += c1;
		
		h1 -= a2;
	}
	
	cout << game.size() << endl;
	for(bool b : game)
		cout << (b ? "STRIKE" : "HEAL") << endl;
	
	return 0;
}
