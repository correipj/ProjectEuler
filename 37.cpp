// https://projecteuler.net/problem=37

#include <iostream>
#include <vector>

#include "../Shared/primes.h"

using namespace std;

unsigned long truncL(unsigned long n) {
	if (n < 10)
		return 0;

	int m = 1;
	while (m < n)
		m *= 10;
	
	return n % (m / 10);
}

unsigned long getFirstDigit(unsigned long n) {
	int m = 1;
	while (m < n)
		m *= 10;

	return n / (m/10);
}

bool isGoodDigit(unsigned long n) {
	switch(n) {
	case 0:
	case 2:
	case 4:
	case 5:
	case 6:
	case 8:
		return false;
	case 1:
	case 3:
	case 7:
	case 9:
		return true;
	}

	return false;
}

bool isTruncPrime(unsigned long n) {
	// First check for digits 2, 4, 5, 6, 8, 0
	// These will appear at end eventually and can never be the last digit
	// of a prime number. Don't check the very first digit since 2 and 5 are
	// themselves prime even though no other primes may end in 2 or 5
	int m = n;
	while (m>10) {
		if (!isGoodDigit(m%10))
			return false;

		m /= 10;
	}

	if (!isPrime(n))
		return false;

	int nR = n;
	while (nR /= 10)
		if (!isPrime(nR))
			return false;

	int nL = n;
	while (nL = truncL(nL))
		if (!isPrime(nL))
			return false;

	return true;
}

int main(int argc, char* argv[]) {
	unsigned int count = 0;
	unsigned long sum = 0;

	for (unsigned long p = 11; count < 11; p+=2) 
		if (isTruncPrime(p)) {
			sum += p;
			count++;
		}

	printf("sum = %lu\n", sum);

	getchar();

	return 0;
}