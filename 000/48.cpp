// https://projecteuler.net/problem=48

#include <iostream>

using namespace std;

typedef unsigned long long uint64_t;

const uint64_t N = 10000000000;

uint64_t selfPower(unsigned int n) {
	uint64_t ret = 1;

	for (int i = 0; i < n; i++) {
		ret *= n;
		ret %= N;
	}

	return ret;
}

int main(int argc, char* argv[]) {
	uint64_t sum = 0;
	for (int i = 1; i < 1000; i++) {
		sum += selfPower(i);
		sum %= N;
	}

	printf("%llu\n", sum);

	getchar();

	return 0;
}