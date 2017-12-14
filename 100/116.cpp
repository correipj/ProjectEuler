// https://projecteuler.net/problem=116
// Red, green or blue tiles

#include <iostream>
#include <map>

using namespace std;

typedef unsigned long long num_t;
typedef pair<unsigned int, unsigned int> pair_t;

map<pair_t, num_t> filled;

num_t fill(unsigned int len, unsigned int b) {
	const pair_t p = make_pair(len, b);

	if (b > len)
		filled[p] = 1;

	if (filled[p])
		return filled[p];

	num_t sum = 1;

	for (int start = 0; start <= len-b; start++)
		sum += fill(start, b);

	return filled[p] = sum;
}


int main(int argc, char* argv[]) {
	// Subtract 3 since not replacing any blocks isn't a valid solution
	printf("%llu\n", fill(50, 2) + fill(50, 3) + fill(50, 4) - 3);

	getchar();

	return 0;
}
