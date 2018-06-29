#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

typedef long long int lli;

struct Axis {
	Axis(lli max){
		coords.insert(0);
		coords.insert(max);
		
		areas.insert(max);
	}
	
	multiset<lli> coords;
	multiset<lli> areas;
};

void divide(Axis& axis, lli position){
	auto up = axis.coords.upper_bound(position);
	
	if(up == axis.coords.end() || position == 0 || position == *axis.coords.rbegin()) return;
	
	lli a = *prev(up), b = *up;
	
	axis.areas.erase(axis.areas.find(b - a)); // old area (only one value)
	axis.areas.insert(position - a); // new area left
	axis.areas.insert(b - position); // new area right
	
	axis.coords.insert(position);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	//fstream cin("input.in");
	
	lli T;
	cin >> T;
	
	for(lli t = 0; t < T; t++){
		lli N, M, Q;
		cin >> N >> M >> Q;
		
		Axis horz(M), vert(N);
		
		bool horizontal;
		lli coord;
		
		for(lli i = 0; i < Q; i++){
			cin >> horizontal >> coord;
			
			if(horizontal)
				divide(horz, coord);
			else
				divide(vert, coord);
			
			lli biggestHorz = *horz.areas.rbegin();
			lli biggestVert = *vert.areas.rbegin();
			
			cout << (biggestHorz * biggestVert) << "\n";
		}
	}
	
	return 0;
}
