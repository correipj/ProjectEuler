// https://projecteuler.net/problem=70

#include <iostream>
#include <vector>
#include "../Shared/primes.h"

using namespace std;

bool isPermutation(unsigned long a, unsigned long b) {
	char buffer[16];
	sprintf(buffer, "%lu", a);
	string s1(buffer);	
	sprintf(buffer, "%lu", b);
	string s2(buffer);

	if (s1.size() != s2.size())
		return false;
	
	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());

	return s1 == s2;
}

int main(int argc, char* argv[]) {
	const unsigned int maxN = 10000000;
	const unsigned int lim = floor(sqrt(maxN));

	unsigned int pLim = primes.size();

	// Find index of first prime greater than sqrt(maxN)
	for (int i = 0; i < primes.size(); i++)
		if (primes[i] > lim) {
			pLim = i;
			break;
		}
	const unsigned int pStart = pLim / 2;

		
	double minRat = 9.9;
	unsigned int minN;

	for(int i = pStart; i < pLim; i++) {
		const unsigned long pi = primes[i];

		for(int j = i; j < primes.size(); j++) {
			if (i == j)
				continue;
			
			const unsigned long pj = primes[j];		

			unsigned long n = pi * pj;

			if (n > maxN)
				continue;
						
			unsigned long t = (pi-1) * (pj-1);

			if (!isPermutation(n, t))
				continue;

			const double rat = (double)n / (double)t;

			if (rat < minRat) {
				minN = n;
				minRat = rat;
			}
		}
	}

	printf("N = %d\n", minN);
	
	getchar();

	return 0;
}

