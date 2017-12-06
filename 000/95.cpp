// https://projecteuler.net/problem=95
// Amicable chains

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "../Shared/primes.h"

using namespace std;

/*	This program is currently pretty damned slow. I'm lucky in that it catches
 *	the correct answer fairly early because running through every possible
 *	starting number under a million takes more time than I am willing to test.
 *	The first thing I'd want to optimize is the sumOfDivisors function.
 *	see: https://www.math.upenn.edu/~deturck/m170/wk3/lecture/sumdiv.html
 *
 */

unsigned long sumOfDivisors(unsigned int n) {
	// Naive implementation
	if (n == 1)
		return 1;

	if (isPrime(n))
		return 1;

	unsigned long sum = 1;

	for (int i = 2; i < n; i++) {
		if (n % i == 0)
			sum += i;
	}

	return sum ;
}

int main(int argc, char* argv[]) {
	unsigned int limN = 1000000;

	// Cache values of SumOfDivisors

	// -1 : unsolved
	//  0 : no chain
	//  n : chain of length n
	vector<long> len(limN + 1, -1);

	unsigned long maxLen = 0;
	unsigned int maxLenN;

	for (int startN = 1; startN < limN; startN++) {
		if (startN % 10000 == 0)
			printf("%d\n", startN);

		// Two cases for startN
		// Case 1:
		// repeated iteration of SoD leads back to startN
		// ie A0 -> A1 -> ... -> Ar -> A0
		// startN is a member of a chain of length r

		// Case 2:
		// repeated iteration leads to a member of a chain
		// ie B0 -> B1 -> ... -> Br -> Ai
		// startN is not a member of a chain (call it length 0?)

		// If current starting number has already been solved, check the next
		if (len[startN] != -1)
			continue;

		unsigned long n = sumOfDivisors(startN);
		vector<unsigned long> chain;
		chain.push_back(n);

		while(1) {
			// If a member in the chain has already been solved,
			// solve all previous members of the chain and the starting num
			if (len[n] > 0) {
				for (auto x : chain)
					len[x] = len[n];

				len[startN] = len[n];

				break;
			}

			n = sumOfDivisors(chain.back());

			// If sequence has formed a chain
			auto it = find(chain.begin(), chain.end(), n);

			if (it != chain.end()) {
				const unsigned int d = distance(it, chain.end());
				if (d == 0)
					printf("WTF1\n");

				// solve all previous members of the chain and the starting num
				for (auto x : chain)
					len[x] = d;

				if (d > maxLen || (d == maxLen && n < maxLenN)) {
					maxLen = d;
					maxLenN = n;
					printf("max = %3d at %d\n", maxLen, maxLenN); 
					getchar();
				}

				break;
			}

			// Check if next member will exceed the limit
			if (n > limN) {
				for (auto x : chain)
					len[x] = 0;

				len[startN] = 0;
				break;
			}

			// Continue with chain
			chain.push_back(n);
		}

	}

	getchar();

	return 0;
}
