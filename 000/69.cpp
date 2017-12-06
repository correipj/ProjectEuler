// https://projecteuler.net/problem=69
// Totient maximum

#include <iostream>
#include "../Shared/primes.h"

using namespace std;

int main(int argc, char* argv[]) {
	double maxD = 0.0;
	for (int i = 1; i < 1000; i++) {
		unsigned long t = totient(i);
		double d = (double)i/(double)t;

		if (d >= maxD) {
			//printf("%8d  %8d  %.2f\n", i, t, d);
			maxD = d;
		}
	}

	// See a pattern in the above?
	// New max comes at i = p1 * p2 * p3 * ... where pn is nth prime
	// Find lowest prime of this form (primorial) less than 10^6
	
	unsigned long prod = 1;
	unsigned long p = 1;
	while(prod*nextPrime(p) < 1000000) {
		p = nextPrime(p);
		prod *= p;
	}
	
	printf("%lu\n", prod);

	getchar();

	return 0;
}

