#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long d(int x, int y){
	if(abs(x - y) > 1)
		return y - x;
	return 0;
}

int main(){
	int N;
	cin >> N;
	
	vector<int> a(N), util(N);
	for(int i = 0; i < N; i++){
		cin >> a[i];
		util[i] = a[i];
	}
	
	sort(util.begin(), util.end());
	
	long long sum = 0;
	for(int i = 0; i < N - 1; i++){
		int x = a[i];
		util.erase(find(util.begin(), util.end(), x));
		
		cout << "=================" << endl;
		cout << "X = " << x <<endl;
		for(int j : util)
			cout << j << " ";
		cout << endl;
		
		int s1 = util.begin() - lower_bound(util.begin(), util.end(), x - 1);
		int s2 = util.begin() - lower_bound(util.begin(), util.end(), x + 1);
		cout << s1 << ", " << s2 << endl;
		
		if(s1 == s2)
			s2--;
		
		for(int j = s1; j < util.size(); j++){
			sum += util[j] - x;
		}
		for(int j = s2; j >= 0; j--){
			sum += util[j] - x;
		}
	}
	
	cout << sum << endl;
	
	return 0;
}
