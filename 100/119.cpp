// https://projecteuler.net/problem=119
// Digit power sum

#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef unsigned long long num_t;

num_t sumOfDigits(num_t n) {
	num_t sum = 0;

	while(n) {
		sum += n%10;
		n /= 10;
	}

	return sum;
}

int main(int argc, char* argv[]) {
	vector<num_t> pows;
	for (num_t i = 0; i <= 100; i++)
		pows.push_back(i);

	set<num_t> digSumPow;
	
	for (num_t n = 10; digSumPow.size() < 30; n *= 10)	
		// If powers of d don't exist up to n, compute missing powers
		for (num_t d = 2; d < pows.size(); d++)
			while(pows[d] < n) {
				pows[d] *= d;
				
				if (sumOfDigits(pows[d]) == d)
					digSumPow.insert(pows[d]);
			}

	int i = 0;
	for (auto x : digSumPow)
		printf("a_%02d = %llu\n", ++i, x);

	getchar();

	return 0;
}
