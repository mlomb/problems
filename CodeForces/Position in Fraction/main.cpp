#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <set>

using namespace std;

int main() {
	long long a, b;
	char c;
	cin >> a >> b >> c;
	
	int result = -2;
	int pos = 0;
	set<long long> visited;
	while(result == -2){
		while(a < b){
			a *= 10;
			if(c == '0' && pos != 0){
				result = pos;
				break;
			}
			pos++;
		}
		if(visited.size() > 20000) // pd. no roba :/
			result = -2;
		if(result != -2)
			break;
		
		long long remainder = a % b;
		
		auto it = visited.lower_bound(remainder);
		if(it != visited.end() && *it == remainder){
			result = -1;
			break;
		}
		visited.insert(remainder);
		
		long long digit = (a - remainder) / b;
		
		//cout << a << " " << remainder << " " << digit << endl;
		
		if((char)(digit + 48) == c){
			result = pos;
			break;
		}
		
		a = remainder * 10;
		pos++;
	}
	
	cout << result << endl;
	
	return 0;
}
