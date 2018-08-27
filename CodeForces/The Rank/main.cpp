#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
	int id;
	int sum;
};

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int N;
	cin >> N;
	
	int a, b, c, d;
	vector<Student> students(N);
	for(int i = 0; i < N; i++) {
		cin >> a >> b >> c >> d;
		students[i].id = i+1;
		students[i].sum += a + b + c + d;
	}
	
	sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
		if(a.sum == b.sum) return a.id < b.id;
		return a.sum > b.sum;
	});
	
	for(int i = 0; i < N; i++) {
		if(students[i].id == 1) {
			cout << (i+1) << endl;
			return 0;
		}
	}
	
	return 0;
}