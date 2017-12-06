// https://projecteuler.net/problem=47

#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "../Shared/primes.h"

using namespace std;

// Using recursion allows us to use the lookup table for primes.
// ex. if p^a divides n then n will have one more factor than n/(p^a)
unsigned int nPrimeFactors(unsigned int n, unsigned int intP = 0) {
	if (n == 1 || isPrime(n))
		return 1;

	unsigned int p = intP;

	while(n >= primes[p]) {
		bool isFact = n%primes[p] == 0;

		while(n % primes[p] == 0)
			n /= primes[p];

		if (isFact)	break;
		
		p++;
	}

	return 1 + nPrimeFactors(n, p);
}

int main(int argc, char* argv[]) {	
	const unsigned int N = 4;
	int counter = 0;

	for (int i = 10; ; i++) {
		if (nPrimeFactors(i) == N)
			counter++;
		else
			counter = 0;

		if (counter == N) {
			printf("%d %d %d %d all have %d prime factors\n", i-3, i-2, i-1, i, N);
			break;
		}
	}

	getchar();

	return 0;
}