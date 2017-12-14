// https://projecteuler.net/problem=128
// Hexagonal tile differences

#include <iostream>
#include <array>
#include <vector>
#include "../Shared/primes.h"

using namespace std;

typedef unsigned long long num_t;

num_t getN(const num_t& ring, const num_t& side, const num_t& offset) {
	if (ring == 0)
		return 1;

	return 2 + 3*ring*(ring-1) + side*ring + offset;
}

array<num_t, 6> getNeighbours(const num_t& n) {
	if (n == 1)
		return {2, 3, 4, 5, 6, 7};

	array<num_t, 6> ret = {0, 0, 0, 0, 0, 0};

	unsigned int ringN = 0;
	num_t x = 1;
	while(x < n) {
		ringN++;
		x += ringN*6;
	}

	unsigned int sideN = 5-(x-n)/ringN;
	unsigned int offN = ringN - (x-n) % ringN - 1;

	if (offN == 0) {		
		ret[0] = getN(ringN-1, sideN, 0);
		ret[1] = getN(ringN, sideN, 1);
		ret[2] = getN(ringN+1, sideN, 1);
		ret[3] = getN(ringN, (sideN+5)%6, ringN-1);			
		ret[4] = getN(ringN+1, sideN, 0);
		ret[5] = getN(ringN+1, (sideN+5)%6, ringN);
	} else {
		if (sideN == 5 && offN == ringN-1) {
			ret[0] = getN(ringN-1, 0, 0);
			ret[3] = getN(ringN, 0, 0);
		} else {
			ret[0] = getN(ringN-1, sideN, offN);
			ret[3] = getN(ringN, sideN, offN+1);
		}
		ret[1] = getN(ringN-1, sideN, offN-1);
		ret[2] = getN(ringN, sideN, offN-1);
		ret[4] = getN(ringN+1, sideN, offN);
		ret[5] = getN(ringN+1, sideN, offN+1);
	}

	return ret;
}

num_t PD(const num_t& n) {
	int count = 0;

	for (auto x : getNeighbours(n))
		count += isPrime((n>x)?(n-x):(x-n));

	return count;
}

int main(int argc, char* argv[]) {
	unsigned int count = 0;
	num_t n = 0;
	const unsigned int maxCount = 2000;
	while(1) {
		if (PD(3*n*(n+1) + 1) == 3)
			count++;

		if (count >= maxCount) {			
			printf("-- %llu\n", 3*n*(n+1) + 1);
			break;
		}
		
		if (PD(3*n*(n+1) + 2) == 3)
			count++;

		if (count >= maxCount) {			
			printf("%llu\n", 3*n*(n+1) + 2);
			break;
		}

		n++;
	}
	
	getchar();

	return 0;
}
