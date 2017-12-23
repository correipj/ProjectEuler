// https://projecteuler.net/problem=183
// Maximum product of parts

#include <iostream>
#include <cmath>
#include "../Shared/primes.h"

using namespace std;

int D(int N) {
	// A is value of k such that f(k) (N/k)^k is maximized
	double a = floor(exp(log((double)N) - 1));

	// compare f(a) and f(a+1)
	int k;
	if (pow((a+1)/a, a) > ((double)N / (a+1.0)))
		k = (int)a;
	else
		k = (int)a+1;


	// Check if N/k is a terminating decimal
	// Compute reduced fraction N'/k'
	// if k' is divisible by a prime other than 2 or 5, then N/k is
	// non-terminating

	int N1 = N;
	int x = 1;
	while(++x <= k)
		if (k % x == 0 && N1 % x == 0) {
			k /= x;
			N1 /= x;
			x = 1;
		}


	if (k == 1)
		return -N;

	for (auto p : primes) {
		if (p > k)
			break;

		if (p == 2 || p == 5)
			continue;

		if (k % p == 0)
			return N;
	}

	return -N;
}


int main(int argc, char* argv[]) {
	int sum = 0;
	for (int N = 5; N <= 10000; N++)
		sum += D(N);

	printf("sum = %d\n", sum);
	
	getchar();

	return 0;
}
