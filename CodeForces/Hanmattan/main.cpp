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
#endif
	
	int x1,y1,x2,y2,xb,yb;
	cin >>x1>>y1>>x2>>y2>>xb>>yb;
	int a=0;
	if(x1<=xb && xb<=x2){
		a++;
	}else if(x1>=xb && xb>=x2){
		a++;
	}
	if(y1<=yb && yb<=y2){
		a++;
	}else if(y1>=yb && yb>=y2){
		a++;
	}
	if(a==2){
		cout<<"Yes"<<endl;
	}else{
		cout<<"No"<<endl;
	}
	return 0;
}