// https://projecteuler.net/problem=90
// Cube digit pairs

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

using namespace std;

vector<unsigned int> squares;

vector<unsigned int> extend(const vector<unsigned int>& v) {
	vector<unsigned int> r(v);

	const bool has6 = find(v.begin(), v.end(), 6) != v.end();
	const bool has9 = find(v.begin(), v.end(), 9) != v.end();
	
	if (has6 && !has9)
		r.push_back(9);
	if (has9 && !has6)
		r.push_back(6);

	return r;
}

bool test(const vector<unsigned int>& a, const vector<unsigned int>& b) {
	vector<bool> sq(9, false);

	set<unsigned int> merged;
	for (auto x : a)
		merged.insert(x);
	for (auto y : b)
		merged.insert(y);

	set<unsigned int> digits = {0, 1, 2, 3, 4, 5, 6, 8, 9};
	for (auto d : digits)
		if (merged.count(d) == 0)
			return false;

	for (auto x : a) {
		for (auto y : b) {
			auto it = find(squares.begin(), squares.end(), 10*x + y);

			if (it != squares.end()) {
				sq[distance(squares.begin(), it)] = true;
				continue;
			}

			it = find(squares.begin(), squares.end(), 10*y + x);

			if (it != squares.end())
				sq[distance(squares.begin(), it)] = true;
		}
	}

	for (auto x : sq)
		if (x == false)
			return false;

	return true;
}

int main(int argc, char* argv[]) {
	for (int i = 1; i <= 9; i++)
		squares.push_back(i*i);

	vector<unsigned int> choice1 (10,0);
	for (int i = 0; i < 6; i++)
		choice1[i] = 1;

	// for keeping track of duplicate solutions
	vector<pair<vector<unsigned int>, vector<unsigned int> > > solns;
	
	vector<unsigned int> a, b;
	unsigned int count = 0;
	do {
		a.clear();
		for (int i = 0; i < choice1.size(); i++)
			if (choice1[i])
				a.push_back(i);

		vector<unsigned int> choice2 (10,0);
		for (int i = 0; i < 6; i++)
			choice2[i] = 1;

		do {
			b.clear();
			for (int i = 0; i < choice2.size(); i++)
				if (choice2[i])
					b.push_back(i);

			if (test(extend(a), extend(b))) 
				if (find(solns.begin(), solns.end(), make_pair(b, a)) == solns.end()) {
					solns.push_back(make_pair(a, b));
					count++;
				}
		} while(next_permutation(choice2.rbegin(), choice2.rend()));
	} while(next_permutation(choice1.rbegin(), choice1.rend()));

	printf("count = %u\n", count);

	getchar();

	return 0;
}
