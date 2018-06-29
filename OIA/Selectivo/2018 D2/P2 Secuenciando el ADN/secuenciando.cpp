#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 52;

string buffer;
int N;
int cant[MAX_N];

int medir(string cad);

char letter(int i) {
	if(i < 26)
		return 'A' + i;
	else
		return 'a' + i - 26;
}
int index(char c) {
	if(c >= 'a' && c <= 'z')
		return c - 'a' + 26;
	else
		return c - 'A';
}

int count_letter(int i) {
	char c = letter(i);
	
	int a = 0, b = N+1;
	while(b-a>1) {
		int mid = (a+b)/2;
		if(medir(string(mid, c)))
			a = mid;
		else
			b = mid;
	}
	
	return a;
}

void combine(int i, int position) {
	char c = letter(i);
	
	string combinated = buffer;
	combinated.insert(combinated.begin() + position, c);
	
	if(medir(combinated)) {
		buffer = combinated;
		cant[i]--;
	}
	position++;
	
	if(cant[i] > 0)
		return combine(i, position);
}

string secuenciar(int N, string s)
{
	::N = N;
	
	int t = 0;
	for(int i = 1; i < s.size(); i++) {
		char c = s[i];
		cant[index(c)] = count_letter(index(c));
		
		t += cant[index(c)];
	}
	cant[index(s[0])] = N - t;
	
	if(s == "AC") { // Subtarea #1
		return string(cant[index('A')], 'A') + string(cant[index('C')], 'C');
	}
	
	vector< pair<int, int> > letters; // apparitions, letter
	for(int i = 0; i < MAX_N; i++) {
		if(cant[i])
			letters.push_back(make_pair(cant[i], i));
	}
	
	sort(letters.begin(), letters.end());
	
	buffer = string(letters[0].first, letter(letters[0].second));
	for(int i = 1; i < letters.size(); i++) {
		combine(letters[i].second, 0);
	}
	
    return buffer;
}
