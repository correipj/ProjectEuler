// https://projecteuler.net/problem=233
// Lattice points on a circle

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#include "../Shared/primes.h"

typedef unsigned long long uint64_t;
typedef unsigned long uint32_t;

using namespace std;

uint32_t countLattice(uint64_t N) {
	uint64_t p = 1;
	uint32_t count = 1;

	while(N > 1 && p < N) {
		p = nextPrime(p);

		int n = 0;
		while (N % p == 0) {
			n++;
			N /= p;
		}

		if (p % 4 == 1)
			count *= 2*n + 1;
	}

	return 4*count;
}

bool isValidMultiplier(uint64_t n) {
	if (n < 2)
		return false;

	if (isPrime(n))
		return n % 4 != 1;

	uint32_t p = 1;

	while(p <= n) {
		p = nextPrime(p);

		int c = 0;
		while(n % p == 0) {
			c++;
			n /= p;
		}

		if (c && p%4 == 1)
			return false;
	}

	return true;
}


// FML just iterating to 10^11 takes 230 seconds or just under 4 minutes
// Iterating to 327435278 only takes 2 seconds,  where 327435278 is the # of N
// such that f(N) = 420 with N in lowest form (ie f(2N) = 420, f(3N) = 420, etc)

#include <ctime>

int main(int argc, char* argv[]) {
	const uint64_t maxMult = 90497738;
	uint32_t count = 1;
	uint64_t thresh = 500;
	uint64_t incr = 500;

	for (int i = 3; i < maxMult; i++) {
		if (i >= thresh) {
			printf("%8d  %7lu\n", i, count);
			thresh += incr;
		}

		if (isValidMultiplier(i))
			count++;
	}

	printf("%lu multipliers\n", count);

	/*vector<uint64_t> myPrimes;

	uint64_t thresh = 500000;
	uint64_t incr = 500000;
	
	const uint64_t p0Max = 4733689;
	const uint64_t p1Max = 7841;
	const uint64_t p2Max = 673;

	unsigned int n0, n1, n2;

	for (uint64_t p = 5; p <= p0Max; p+=4) {
		if (p >= thresh) {
			printf("%llu\n", p);
			thresh += incr;
		}

		if (!isPrime(p))
			continue;

		if (p == p0Max)
			n0 = myPrimes.size();		
		if (p == p1Max)
			n1 = myPrimes.size();		
		if (p == p2Max)
			n2 = myPrimes.size();

		myPrimes.push_back(p);
	}

	printf("%lu primes <= %llu\n", myPrimes.size(), p0Max);
	printf("n0 = %d, n1 = %d, n2 = %d\n", n0, n1, n2);
	unsigned int nCombos = 0;

	for (unsigned int i = 0; i < n0; i++) {
		for (unsigned int j = 0; j < n1; j++) {
			if (j == i)
				continue;

			for (unsigned int k = 0; k < n2; k++) {				
				if (k == j || k == i)
					continue;

				nCombos++;
			}
		}
	}

	printf("%lu combos\n", nCombos);*/

	getchar();

	return 0;
}