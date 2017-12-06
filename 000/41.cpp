// https://projecteuler.net/problem=41

#include <iostream>
#include <string>
#include <algorithm>
#include "../Shared/primes.h"

using namespace std;

int main(int argc, char* argv[]) {
	string s = "7654321";
	unsigned long n;
	bool found = false;
	do {
		switch (s.back()) {
		case '0':
		case '2':
		case '4':
		case '5':
		case '6':
		case '8':
			continue;
		default:
			break;
		}
		
		n = atol(s.c_str());

		if (isPrime(n)) {
			found = true;
			break;
		}
	} while(prev_permutation(s.begin(), s.end()));
	
	if (found)
		printf("prime = %lu\n", n);
	else
		printf("try shorter initial string\n");

	getchar();

	return 0;
}

