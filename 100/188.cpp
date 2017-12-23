// https://projecteuler.net/problem=188
// The hyperexponentiation of a number

#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long num_t;

const num_t modBase = 100000000;

num_t expMod(const num_t& b, const num_t& e) {
	num_t r = 1;

	for (num_t n = 1; n <= e; n++)
		r = (r * b) % modBase;

	return r;
}

int main(int argc, char* argv[]) {
	num_t b = 1777;
	num_t e = 1855;

	vector<num_t> hypExp;
	hypExp.push_back(1);
	hypExp.push_back(b);

	for (num_t n = 2; n <= e; n++) {
		hypExp.push_back(expMod(b, hypExp.back()));

		if (hypExp[n] == hypExp[n-1])
			break;
	}

	printf("%lld ^^ %lld == %lld\n", b, e, hypExp.back());
	
	getchar();

	return 0;
}
