#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define LSB(i) (i & (-i))

const int SIZE = 1000000000 + 100;

void add(int index, int value, unordered_map<int, int>& ftree){
	while(index <= SIZE){
		ftree[index] += value;
		index += LSB(index);
	}
}

int get(int index, unordered_map<int, int>& ftree){
	int result = 0;
	while(index > 0){
		result += ftree[index];
		index -= LSB(index);
	}
	return result;
}

struct Number {
	int num;
	int pos;
	
	bool operator<(const Number& o){
		return num < o.num;
	}
};

struct Query {
	int pos;
	int i, j;
	int k;
	int result;
	
	bool operator<(const Query& o){
		return k > o.k;
	}
};

int main() {
	cin.tie();
	ios::sync_with_stdio(false);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	unordered_map<int, int> ftree; // lazy prop

	int N, Q;
	
	cin >> N;
	vector<Number> nums(N);
	
	for(int i = 0; i < N; i++){
		nums[i].pos = i;
		cin >> nums[i].num;
	}
	
	cin >> Q;
	vector<Query> queries(Q);
	
	for(int i = 0; i < Q; i++){
		queries[i].pos = i;
		cin >> queries[i].i >> queries[i].j >> queries[i].k;
	}
	
	sort(nums.begin(), nums.end()); // sort by num descending
	sort(queries.begin(), queries.end()); // sort by k descending
	
	for(Query& q : queries) {
		//cout << "Query: " << q.i << ", " << q.j << " k= " << q.k << endl;
		while(!nums.empty() && nums.back().num > q.k){
			//cout << "Added " << nums.back().num << " at " << (nums.back().pos + 1) << endl;
			add(nums.back().pos + 1, 1, ftree);
			nums.pop_back();
		}
		
		q.result = get(q.j, ftree) - get(q.i - 1, ftree);
	}
	
	sort(queries.begin(), queries.end(), [](const Query& a, const Query& b){ // sort by pos ascending
		return a.pos < b.pos;
	});
	
	for(Query& q : queries) {
		cout << q.result << "\n";
	}
	
	return 0;
}
