// https://projecteuler.net/problem=145
// How many reversible numbers are there below one-billion?

#include <iostream>
#include <map>

using namespace std;

typedef unsigned long num_t;

bool oddDigits(num_t n) {
	while(n) {
		if (n % 2 == 0)
			return false;

		n /= 10;
	}

	return true;
}

num_t reverse(num_t n) {
	num_t r = 0;

	while(n) {
		r *= 10;
		r += n%10;
		n /= 10;
	}

	return r;
}

int main(int argc, char* argv[]) {
	// No reversable numbers between 1E8 and 1E9
	const num_t lim = 100000000;
	
	unsigned int count = 0;
	for (num_t n = 0; n < lim; n++) {
		// No leading / trailing digits allowed in n or reverse(n)
		if (n % 10 == 0)
			continue;

		const num_t r = reverse(n);

		// Test pair once, count twice
		if (r < n)
			continue;

		if (oddDigits(n + r))
			count += 2;
	}

	printf("count = %lu\n", count);

	getchar();

	return 0;
}
