// https://projecteuler.net/problem=124
// Ordered radicals

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include "../Shared/primes.h"

using namespace std;

typedef unsigned long num_t;

struct radn_t {
	num_t n, rad;

	bool operator< (const radn_t& rhs) const {
		return rad < rhs.rad || (rad == rhs.rad && n < rhs.n);
	}
};


int main(int argc, char* argv[]) {	
	const num_t maxN = 100000;

	vector<radn_t> rads;

	for (num_t n = 1; n <= maxN; n++) {
		radn_t temp;
		temp.n = n;
		temp.rad = 1;

		rads.push_back(temp);
	}

	num_t p = 2;
	do {
		for (num_t n = p; n <= maxN; n += p)
			rads[n-1].rad *= p;

		p = nextPrime(p);
	} while(p < maxN);

	sort(rads.begin(), rads.end());
	
	printf("E(10000) = %lu\n", rads[10000-1].n);
	
	getchar();

	return 0;
}
