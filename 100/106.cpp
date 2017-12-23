// https://projecteuler.net/problem=106
// Special subset sums: meta-testing

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef vector<int> sel_t;

unsigned int SIZE = 12;

bool testPair(const sel_t& a, const sel_t& b) {
	// Test for disjoint
	for (int i = 0; i < a.size(); i++)
		if (a[i] == 1 && b[i] == 1)
			return false;
	
	// Cumulative sum of a and b
	vector<int> ca(1, a.front());
	vector<int> cb(1, b.front());

	for (int i = 1; i < a.size(); i++) {
		ca.push_back(a[i] + ca.back());
		cb.push_back(b[i] + cb.back());
	}

	// Find first non-equal pair
	int i = 0;
	while (ca[i] == cb[i])
		i++;

	// If ca starts out greater than cb but swaps halfway through
	// this subset pair must be tested
	bool greater = ca[i] > cb[i];

	for (; i < a.size(); i++) {
		if (greater && ca[i] < cb[i])
			return true;

		if (!greater && ca[i] > cb[i])
			return true;
	}

	return false;
}


int main(int argc, char* argv[]) {
	int count = 0;
	for (int n = 2; 2*n <= SIZE; n++) {	
		sel_t sel(SIZE, 0);
		for (int i = 0; i < n; i++)
			sel[i] = 1;

		vector<sel_t> sels;
		do {
			sels.push_back(sel);
		} while(prev_permutation(sel.begin(), sel.end()));

		for (int i = 0; i < sels.size(); i++)
			for (int j = i+1; j < sels.size(); j++)
				if (testPair(sels[i], sels[j]))
					count++;
	}

	printf("N = %d   count = %d\n", SIZE, count);

	
	getchar();

	return 0;
}
