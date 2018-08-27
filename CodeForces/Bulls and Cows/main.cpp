#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <string>
#include <sstream>

using namespace std;

struct Opt {
	string num;
	int bien_lugar;
	int bien_nums;
};

string getnum(int n) {
	stringstream ss;
	ss << n;
	string sss = ss.str();
	
	int dif = 4 - sss.length();
	string f = string(dif, '0');
	
	string final = f + sss;
	
	set<char> digits;
	for(char c : final)
		digits.insert(c);
	if(digits.size() != final.size())
		return "";
	
	return final;
}

int main() {
#ifdef LOCAL
	ifstream cin("input.in");
#endif
	
	int N;
	cin >> N;
	
	vector<Opt> num(N);
	for(int i = 0; i < N; i++) {
		int n;
		cin >> n;
		num[i].num = getnum(n);
		cin >> num[i].bien_lugar >> num[i].bien_nums;
	}
	
	int res=-1;
	for(int i = 0; i <= 9999; i++) {
		string s = getnum(i);
		if(s.length() == 0) continue;
		//cout << s << endl;
			
		bool ok = true;
		for(Opt& o : num) {
			int lugares_bien = 0;
			int esta_bien = 0;
			
			for(int j = 0; j < 4; j++) {
				if(s[j] == o.num[j]) {
					lugares_bien++;
				}
			}
			
			for(int j = 0; j < 4; j++) {
				for(int k = 0; k < 4; k++) {
					if(s[j] == o.num[k] && j != k) {
						esta_bien++;
					}
				}
			}
			
			if(o.bien_lugar != lugares_bien || o.bien_nums != esta_bien) {
				ok = false;
				break;
			}
		}
		
		if(ok) {
			if(res==-1) {
				res=i;
			}else{
				cout << "Need more data" << endl;
				return 0;
			}
		}
	}
	
	cout << (res == -1 ? "Incorrect data" : getnum(res)) << endl;
	
	return 0;
}