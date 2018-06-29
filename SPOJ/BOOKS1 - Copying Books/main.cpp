#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

typedef long long int lli;

using namespace std;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
#ifdef LOCAL
	fstream cin("input.in");
#endif
	
	lli T;
	cin >> T;
		
	vector<lli> nums;
	
	for(lli t = 0; t < T; t++){
		lli M, K;
		cin >> M >> K;
		
		nums.resize(M);
		
		lli sum = 0, mx = 0;
		for(lli i = 0; i < M; i++){
			cin >> nums[i];
			sum += nums[i];
			mx = max(mx, nums[i]);
		}
		
		lli lo = mx, hi = sum + 1;
		while(hi - lo > 1) {
			lli mid = (lo + hi) / 2;
			
			lli scribers = 0, pages = 0;
			for(lli i = M - 1; i >= 0; i--){
				if(pages + nums[i] >= mid) {
					scribers++;
					pages = 0;
				}
				pages += nums[i];
			}
			
			//cout << "mid= " << mid << " ; scribers= " << scribers << endl;
			
			if(scribers >= K)
				lo = mid;
			else
				hi = mid;
		}
		
		// lo ahora es el maximo que puede tener cualquier scriber solo
		//cout << lo << endl;
		
		vector<lli> result;
		result.reserve(M + K);
		
		sum = 0;
		lli scribers = 1;
		for(lli i = M - 1; i >= 0; i--){
			if(sum != 0 && (sum + nums[i] > lo || K - scribers > i)) {
				result.push_back(-1);
				scribers++;
				sum = nums[i];
			} else sum += nums[i];
			
			result.push_back(nums[i]);
		}
		
		reverse(result.begin(), result.end());
		
		for(lli i : result){
			if(i == -1) cout << "/ ";
			else cout << i << " ";
		}
		cout << "\n";
	}
	
	return 0;
}
