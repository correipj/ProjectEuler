// https://projecteuler.net/problem=46
// Goldbach's other conjecture

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131,
137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223,
227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311,
313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503,
509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613,
617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719,
727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827,
829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
947, 953, 967, 971, 977, 983, 991, 997};

// Can only verify prime numbers < 1022117
#define MAX_PRIME	1022117
bool isPrime(unsigned int n) {
	if (n < 2)
		return false;

	for (auto p : primes) {
		if (p >= n)
			break;

		if (n % p == 0)
			return false;
	}

	return true;
}

unsigned int nextPrime(unsigned int n) {
	if (n % 2 == 0)
		n--;
	
	while(!isPrime(n+2))
		n+=2;

	return n+2;
}

int main(int argc, char* argv[]) {
	int n = 5;
	while (n += 2) {
		if (isPrime(n))
			continue;

		bool foundPrime = false;

		// Find biggest square 's' to fit in form
		// n = p + 2*s^2

		int s = floor(sqrt(n/2));

		// Check if remainder is prime for all 1..s
		for (int i = s; i >= 1; i--)
			if (isPrime(n - 2*i*i)) {
				foundPrime = true;
				break;
			}

		if (!foundPrime) {
			printf("%d violates conjecture\n", n);
			break;
		}
	}

	getchar();

	return 0;
}

