// https://projecteuler.net/problem=125
// Palindromic sums

#include <iostream>
#include <set>

using namespace std;

typedef unsigned long long num_t;

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
	num_t lim = 100000000;

	// Store palindromic numbers in a set to avoid counting duplicates twice
	set<num_t> palin;

	for (num_t i = 1; i*i < lim; i++) {
		num_t sqSum = 0;

		for (num_t j = i; ; j++) {
			sqSum += j*j;

			if (sqSum > lim)
				break;

			if (j > i && sqSum == reverse(sqSum))
				palin.insert(sqSum);
			
		}
	}

	num_t sum = 0;
	for (auto p : palin)
		sum += p;

	printf("sum = %llu\n", sum);
	
	getchar();

	return 0;
}
