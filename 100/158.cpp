// https://projecteuler.net/problem=158
// Exploring strings for which only one character comes lexicographically 
// after its neighbour to the left

#include <iostream>

using namespace std;

typedef unsigned long long num_t;

// Return 26 choose N
num_t choose26N (num_t N) {
	num_t ret = 1;

	for (num_t i = 0; i < N; i++) {
		ret *= (26 - i);
		ret /= (i + 1);
	}

	return ret;
}

num_t euler(num_t n) {
	if (n < 2)
		return 0;

	return n - 1 + 2*euler(n-1);
}

int main(int argc, char* argv[]) {
	num_t maxP = 1;

	for (num_t n = 2; n <= 26; n++) {
		num_t p = choose26N(n) * euler(n);
		printf("p(%2llu) = %llu\n", n, p);

		if (p > maxP)
			maxP = p;
	}

	printf("max = %llu\n", maxP);

	getchar();

	return 0;
}
