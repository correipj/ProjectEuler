// https://projecteuler.net/problem=58
// Spiral primes

#include <iostream>
#include "../Shared/primes.h"

using namespace std;

// Holy makanaw this problem needs some big ass primes

int main(int argc, char* argv[]) {
	unsigned int count = 0;
	
	unsigned long long a = 1;
	unsigned long iter;
	for (iter = 1; ; iter++) {
		for (int i = 0; i < 3; i++) {
			a += 2*iter;

			if (isPrime(a))
				count++;
		}
		a += 2*iter;

		if (a > MAX_PRIME_CALC) {
			printf("problemo!\n");
			getchar();
		}

		if (10.0*count < 4.0*iter + 1.0)
			break;
	}

	printf("len = %d\n", 2*iter+1);


	getchar();

	return 0;
}

