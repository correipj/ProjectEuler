// https://projecteuler.net/problem=77
// Prime summations

#include <iostream>
#include "../Shared/primes.h"

using namespace std;

// 2ez
// There are smarter ways to compute this, namely as a reccurance relation
// but this method computes the answer in under a second.

unsigned long N(unsigned long a, unsigned long b) {
	if (a == 0)
		return 1;

	if (b == 2 && a%2 == 1)
		return 0;

	unsigned long sum = 0;
	
	for (auto p : primes) {
		if (p > b)
			break;

		if (p > a)
			break;
		
		sum += N(a - p, p);
	}

	return sum;
}

int main(int argc, char* argv[]) {
	for (int i = 2; i < 200; i++) {
		unsigned long n = N(i, i);
		printf("N(%d) = %lu\n", i, n);

		if (n > 5000)
			break;
	}
	
	getchar();

	return 0;
}

