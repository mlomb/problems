class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		vector<int> result;
		deque<int> v;
		
		int i = 0, j = 0;
		for(int pos = 0; pos < nums.size(); pos++) {
			// advance i
			if(pos >= k){
				if(v.front() == i)
					v.pop_front();
				i++;
			}
			
			// advance j
			while(!v.empty() && nums[j] >= nums[v.back()])
				v.pop_back();
			v.push_back(j);
			j++;
			
			if(pos >= k - 1)
				result.push_back(nums[v.front()]);
		}
		
		return result;
	}
};