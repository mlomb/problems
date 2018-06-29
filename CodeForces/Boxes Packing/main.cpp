#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	int N;
	cin >> N;
	
	vector<int> boxes(N);
	for(int i = 0; i < N; i++)
		cin >> boxes[i];
	
	sort(boxes.begin(), boxes.end(), greater<int>());
	
	int visible = 0;
	while(boxes.size() > 0) {
		visible++;
		int size = *boxes.begin();
		boxes.erase(boxes.begin());
		
		for (auto it = boxes.begin(); it != boxes.end();) {
			int subsize = *it;
			if(subsize < size){
				size = subsize;
				it = boxes.erase(it);
			} else it++;
		}
	}
	
	cout << visible << endl;
	
	return 0;
}
