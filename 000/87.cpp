// https://projecteuler.net/problem=87
// Prime power triples

#include <iostream>
#include <vector>
#include <cmath>
#include "../Shared/primes.h"

using namespace std;

int main(int argc, char* argv[]) {
	const unsigned long N = 50000000;
	const unsigned int maxPow2 = pow((double)N, 1.0/2.0);
	const unsigned int maxPow3 = pow((double)N, 1.0/3.0);
	const unsigned int maxPow4 = pow((double)N, 1.0/4.0);

	// Find indicies corresponding to max powers
	unsigned int n2, n3, n4;
	for (int i = 0; i < primes.size(); i++)
		if (primes[i] > maxPow2) {
			n2 = i;
			break;
		}
	for (int i = 0; i < primes.size(); i++)
		if (primes[i] > maxPow3) {
			n3 = i;
			break;
		}
	for (int i = 0; i < primes.size(); i++)
		if (primes[i] > maxPow4) {
			n4 = i;
			break;
		}

	vector<unsigned int> found(N+1, 0);	
	unsigned int count = 0;

	for (int i = 0; i < n2; i++) {		
		const unsigned int N2 = primes[i]*primes[i];
		for (int j = 0; j < n3; j++) {
			const unsigned int N3 = primes[j]*primes[j]*primes[j];

			if (N2 + N3 > N)
				continue;

			for (int k = 0; k < n4; k++) {
				const unsigned int N4 = primes[k]*primes[k]*primes[k]*primes[k];

				if (N2 + N3 + N4 > N)
					continue;

				if (found[N2+N3+N4] == 0)
					count++;

				found[N2+N3+N4] = 1;
			}
		}
	}

	printf("count = %d\n", count);
	getchar();

	return 0;
}

