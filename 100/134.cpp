// https://projecteuler.net/problem=134
// Prime pair connection

#include <iostream>
#include "../Shared/primes.h"

using namespace std;

typedef long long num_t;

// Round a/b towards negative infinity
// (integer division rounds towards 0)
num_t floorDiv(const num_t& a, const num_t& b) {
	return (num_t)floor((double)a/(double)b);
}

// solve linear diophantine equation  a*n + b*k = c  for smallest n > 0
num_t solveDiophantine(num_t a, num_t b, num_t c) {
	// Use extended euclidian algorithm to compute

	num_t currQ = 0, lastQ = 0;
	num_t currR = a, lastR = b;
	num_t currS = 1, lastS = 0;

	for (int i = 2; currR != 0; i++) {
		const num_t q = currQ;
		const num_t r = currR;
		const num_t s = currS;

		currQ = floorDiv(lastR, currR);
		currR = lastR - currR * currQ;
		currS = lastS - currS * currQ;

		lastQ = q;
		lastR = r;
		lastS = s;
	}

	// Find particular solution n0	
	const num_t n0 = lastS * c;


	// Find general solution:
	// n = n0 - b*i	
	const num_t i = (num_t)ceil((double)n0 / (double)b);

	return n0 - b*i;
}

int main(int argc, char* argv[]) {
	num_t maxP = 1000000;
	num_t p1 = 5;
	num_t sum = 0;

	while(p1 < maxP) {
		num_t p2 = nextPrime(p1);
		
		num_t offset = 1;
		while (offset < p1)
			offset *= 10;

		num_t A = (offset+p1) % p2;
		num_t B = ((2*offset+p1) % p2) - A;

		num_t n;
		if (B > 0)
			n = solveDiophantine( B, -p2, B-A);
		else if (B < 0)
			n = solveDiophantine(-B, -p2, A-B);

		sum += n*offset + p1;

		p1 = p2;

	}

	printf("sum = %lld\n", sum);
	
	getchar();

	return 0;
}
