// https://projecteuler.net/problem=78
// Coin partitions

#include <iostream>
#include <vector>

using namespace std;

// This is going to be a really fun problem. Such a simple problem statement
// and so much meath hidden under the surface.
// Reading:
// http://en.wikipedia.org/wiki/Partition_(number_theory)
// http://en.wikipedia.org/wiki/Pentagonal_number
// http://en.wikipedia.org/wiki/Pentagonal_number_theorem

// http://mathworld.wolfram.com/PartitionFunctionP.html
// Search for recurrence equation

// Using recurrance equation we can find p(n) as linear combination of p(n-k)
// k is generalized pentagonal number
// Since these are summed together, the entire number doesn't have to be
// calculated, just the sum mod 10^6, which can be performed at every addition

// p(416) is highest partition that can fit in uint64_t, so taking the modulo
// is a necessity

int main(int argc, char* argv[]) {
	const unsigned long LIM = 999999;

	vector<long> penta;
	for (int i = 1; ; i++) {
		penta.push_back( i*( 3*i-1)/2);	
		penta.push_back(-i*(-3*i-1)/2);

		if (penta.back() > LIM)
			break;
	}
	
	const long M = 1000000;
	vector<long> p(2, 1);	// p[0] == p[1] == 1

	for (int i = 2; i <= LIM; i++) {
		bool debug = i == 128;

		long sum = 0;

		for (int j = 0; j < penta.size(); j++) {
			if (penta[j] > i)
				break;

			if (j/2 % 2 == 0)
				sum += p[i - penta[j]];
			else
				sum -= p[i - penta[j]];

			sum %= M;
		}

		if (sum < 0)
			sum += M;

		p.push_back(sum);

		if (sum == 0) {			
			printf("p(%7d) is divisible by 1000000\n", i);
			break;
		}
	}
	
	getchar();

	return 0;
}

