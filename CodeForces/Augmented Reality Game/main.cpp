#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

typedef long long int lli;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int N;
	cin >> N;
	
	int sum=0;
	int mn=0;
	int key;
	for(int i = 0; i < N; i++) {
		cin >> key;
		sum+=key;
		mn=max(mn,key);
	}
	
	if(N <=2){cout<<0<<endl;return 0;}

	cout << min(sum/3,sum-mn)<< endl;


	return 0;
}