// https://projecteuler.net/problem=97
// Large non-mersenne prime

#include <iostream>

using namespace std;

// 2ez

int main(int argc, char* argv[]) {
	const unsigned long long A = 7830457;
	const unsigned long long B = 28433;
	const unsigned long long base = 10000000000;

	unsigned long long n = 1;

	for (unsigned long i = 0; i < A; i++)
		n = (n * 2) % base;
	n = (n * B) % base;
	n = (n + 1) % base;

	printf("n = %llu\n", n);
	
	getchar();

	return 0;
}

