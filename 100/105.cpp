// https://projecteuler.net/problem=105
// Special subset sums: testing

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef vector<int> sel_t;
typedef vector<int> set_t;

unsigned int sumSet(const set_t& S) {
	 unsigned int sum = 0;
	 for (auto x : S)
		 sum += x;
	 return sum;
}

bool testSet(const set_t& S) {
	// Test condition 1
	set<unsigned int> sums;
	for (int n = 1; n <= (S.size()+1)/2; n++) {		
		sel_t sel(S.size(), 0);
		for (int i = 0; i < n; i++)
			sel[i] = 1;

		do {
			unsigned int sum = 0;
			for (int i = 0; i < S.size(); i++)
				if (sel[i] == 1)
					sum += S[i];
			
			if (sums.count(sum) == 1)
				return false;

			sums.insert(sum);			
		} while(prev_permutation(sel.begin(), sel.end()));
	}

	// Test condition 2
	unsigned int sumFirst = S.front();	// Sum of first n+1 items
	unsigned int sumLast = 0;			// Sum of last n items

	for (int i = 1; i < S.size()-i; i++) {
		sumFirst += S[i];
		sumLast += S[S.size()-i];

		if (sumFirst < sumLast)
			return false;
	}

	return true;
}

int main(int argc, char* argv[]) {
	ifstream fin("p105_sets.txt");

	unsigned int sum = 0;

	while(fin.good()) {
		vector<int> v;
		int i;
		char c;

		fin >> i;
		v.push_back(i);

		while(fin.peek() == ',') {
			fin >> c >> i;
			v.push_back(i);
		}

		sort(v.begin(), v.end());

		if (testSet(v))
			sum += sumSet(v);
	}

	fin.close();

	printf("sum = %u\n", sum);
	
	getchar();

	return 0;
}
