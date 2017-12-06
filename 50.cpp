// https://projecteuler.net/problem=50

#include <iostream>
#include <string>
#include <algorithm>

#include "../Shared/primes.h"

using namespace std;

// Construct an array of sums of primes, ie
//		v[0] = 0
//		v[1] = 2
//		v[2] = 2 + 3
//		v[3] = 2 + 3 + 5
//		... etc
// A sum of consecutive primes can be represented as a difference in entries in
// this array. ex:
// sum of 2 ... 13 = v[6] - v[0]
// sum of 5 ... 23 = v[9] - v[2]
// Find the greatest D such that v[a + D] - v[D] is prime and < 1 million.
// 
int main(int argc, char* argv[]) {
	const unsigned int sumLimit = 1000000;

	vector<unsigned long long> primeSum(1);
	for (auto p : primes) {
		primeSum.push_back(p + primeSum.back());

		if (primeSum.back() > sumLimit)
			break;
	}

	unsigned int maxSum = 0;
	unsigned int maxDiff = 0;

	for (int diff = 1; primeSum[diff] < sumLimit; diff++) 
		for (int i = diff; i < primeSum.size(); i++) {
			if (primeSum[i] - primeSum[i-diff] > sumLimit)
				break;

			if (isPrime(primeSum[i] - primeSum[i-diff])) {
				maxDiff = diff;
				maxSum = primeSum[i] - primeSum[i-diff];
			}
		}
	
	printf("%u consecutive primes sum to %u\n", maxDiff, maxSum);

	getchar();

	return 0;
}