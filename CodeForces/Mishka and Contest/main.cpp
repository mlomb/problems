#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_N = 100 + 10;

int nums[MAX_N];
int N, K;

int eat(int start, int direction) {
	int i = start;
	
	while(i+direction >= 0 && i+direction < N && nums[i + direction] <= K)
		i += direction;
	
	return i;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif

	cin >> N >> K;
	
	for(int i = 0; i < N; i++)
		cin >> nums[i];
	
	int l = eat(-1,  1); // ->
	int r = eat( N, -1); // <-
	
	//cout << l << ", " << r << endl;
	
	int p = (l + 1) + (N - r);
	if(l >= r) // intersection
		p -= l - r + 1;
	
	cout << p << '\n';
	
	return 0;
}
