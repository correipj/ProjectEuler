// https://projecteuler.net/problem=78
// Coin partitions

#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <cmath>

using namespace std;

typedef unsigned long long uint64_t;

map<pair<uint64_t, uint64_t>, uint64_t> checked;

uint64_t p(uint64_t n, uint64_t l) {
	if (n <= 1 || l == 1)
		return 1;

	auto nl = make_pair(n, min(n, l));
	
	if (checked[nl] != 0)
		return checked[nl];

	uint64_t sum = 0;

	if (l < n) {
		for (int i = 1; i <= l; i++) 
			sum += p(n-i, i);
	} else {
		for (int i = 1; i <= n; i++)
			sum += p(i-1, n-i+1);
	}
	
	checked[nl] = sum;

	return sum;
}

// This is going to be a really fun problem. Such a simple problem statement
// and so much meath hidden under the surface.
// Reading:
// http://en.wikipedia.org/wiki/Partition_(number_theory)
// http://en.wikipedia.org/wiki/Pentagonal_number
// http://en.wikipedia.org/wiki/Pentagonal_number_theorem

// http://mathworld.wolfram.com/PartitionFunctionP.html
// Search for recurrence equation

int main(int argc, char* argv[]) {
	for (uint64_t i = 4; i < 400; i += 5) {
		uint64_t n = p(i, i);

		if (n % 25 == 0) {
			printf("%3llu %20llu", i, n);

			if (n % 125 == 0)
				printf(" ---");
			printf("\n");
		}
	}
	
	getchar();

	return 0;
}

