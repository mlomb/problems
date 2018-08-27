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
	
	int N;
	cin>>N;
	long long pot[31];
	pot[0]=1;
	for(int i=1;i<31;i++){
		pot[i]=pot[i-1]*2;
	}
	for(int i=0;i<N;i++){
		int a;
		cin>>a;
		cout<<pot[a]-1<<endl;
	}
	return 0;
}