// https://projecteuler.net/problem=76
// Counting summations

#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

typedef unsigned long long uint64_t;

map<pair<uint64_t, uint64_t>, uint64_t> checked;

uint64_t p(uint64_t n, uint64_t l) {
	if (n <= 1 || l == 1)
		return 1;

	auto nl = make_pair(n, min(n, l));
	
	if (checked[nl] != 0)
		return checked[nl];

	uint64_t sum = 0;

	if (l < n) {
		for (int i = 1; i <= l; i++) 
			sum += p(n-i, i);
	} else {
		for (int i = 1; i <= n; i++)
			sum += p(i-1, n-i+1);
	}
	
	checked[nl] = sum;

	return sum;
}

int main(int argc, char* argv[]) {
	printf("%lu\n", p(100, 100) - 1);
	
	getchar();

	return 0;
}

