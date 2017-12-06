// https://projecteuler.net/problem=72
// Counting fractions

#include <iostream>
#include <vector>
#include "../Shared/primes.h"

using namespace std;

// I'm pretty proud of this solution. Faster than most on the forums.
// Uses totient relation
// phi(p*n) = phi(p)*phi(n)*d/phi(d), where d=gcd(p,n)
// If p is prime, then d == 1 or d == p

// See wiki article on Totient Function
// https://en.wikipedia.org/wiki/Euler%27s_totient_function#Other_formulae

int main(int argc, char* argv[]) {
	const unsigned long N = 1000000;
	vector<unsigned long> tot (N+1, 0);	
	tot[1] = 1;

	// index of first prime > sqrt(N)
	// avoids having to check more primes than necessary
	unsigned int primeN = 0;
	while(primes[++primeN] < ceil(sqrt(N)));

	// Calculate all totient(n) for n <= 10^6
	for (int n = 1; n <= N; n++) {
		// If a totient value hasn't been calculated yet for n, this means
		// n must be prime. totient(prime) = prime-1
		if (tot[n] == 0)
			tot[n] = n-1;

		for (int i = 0; i < primeN; i++) {
			const unsigned long p = primes[i];
			if (p*n > N)
				break;

			if (n < p)
				continue;

			if (n % p == 0)
				tot[p*n] = p*tot[n];
			else
				tot[p*n] = tot[p]*tot[n];
		}
	}

	unsigned long long sum = 0;
	for (auto t : tot)
		sum += (unsigned long long)t;

	sum -= tot[1];	// 1/1 isnt a fraction

	printf("sum = %llu\n", sum);
	
	getchar();

	return 0;
}

