// https://projecteuler.net/problem=88
// Product-sum numbers

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// Increments v, starting with least significant element, moving to more
// significant elements when a calculated k value is greater than maxK
vector<unsigned int> incr(const vector<unsigned int>& v, unsigned int maxK) {
	vector<unsigned int> ret = v;

	int d = ret.size()-1;
	ret[d]++;

	while(d >= 0) {
		unsigned int sum = 0;	// sum of all non-zero items
		unsigned int prod = 1;	// product of all non-zero items
		unsigned int n = 0;		// number of non-zero items
		for (auto x : ret)
			if (x) {
				n++;
				sum += x;
				prod *= x;
			}

		if (n + prod - sum <= maxK)
			return ret;

		if (d == 0)
			return vector<unsigned int>(v.size(), 0);

		d--;
		ret[d]++;

		for (int i = d+1; i < ret.size(); i++) {
			if (ret[d] == 1)
				ret[i] = 2;
			else
				ret[i] = ret[d];
		}		
	}

	return vector<unsigned int>(v.size(), 0);
}

int main(int argc, char* argv[]) {
	const unsigned int maxK = 12000;
	
	vector<unsigned int> v = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};
	vector<unsigned int> mins(maxK+1, 4294967295);

	unsigned int last = 0;

	do {
		unsigned int sum = 0;	// sum of all non-zero items
		unsigned int prod = 1;	// product of all non-zero items
		unsigned int n = 0;		// number of non-zero items
		for (auto x : v)
			if (x) {
				n++;
				sum += x;
				prod *= x;
			}

		unsigned int k = n + prod - sum;

		mins[k] = min(mins[k], prod);

		v = incr(v, maxK);
	} while(v.back());
	
	set<unsigned int> kSet;
	for (int i = 2; i < mins.size(); i++)
		kSet.insert(mins[i]);

	unsigned int sum = 0;
	for (auto s : kSet)
		sum += s;

	printf("sum of unique elements = %d\n", sum);
	
	getchar();

	return 0;
}