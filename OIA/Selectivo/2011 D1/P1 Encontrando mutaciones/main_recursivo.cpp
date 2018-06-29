#include <fstream>
#include <cassert>
#include <limits.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>

using namespace std;

int mutacionesBest = INT_MAX;
int N, M, K;
string diff_N, diff_M;

void s(int i, int j, int mut) {
	bool equal = diff_N[i] == diff_M[j];
	if (!equal)
		mut++;

	if (i == N && j == M) {
		mutacionesBest = min(mutacionesBest, mut);
		return;
	}
	else if (mut > mutacionesBest || mut > K)
		return;

	bool ni = i < N;
	bool nj = j < M;

	if (ni && nj)
		s(i + 1, j + 1, mut);
	if (!equal) {
		if (ni)
			s(i + 1, j, mut);
		if (nj)
			s(i, j + 1, mut);
	}
}

int main() {
	ifstream fin("adn.in");
	fin >> N >> M >> K;

	string adn_N, adn_M;
	fin >> diff_N >> diff_M;

	N = diff_N.length();
	M = diff_M.length();
	s(0, 0, 0);

	ofstream fout("adn.out");
	if (mutacionesBest > K)
		fout << "Muy distintas." << endl;
	else
		fout << mutacionesBest << endl;

	return 0;
}
