// https://projecteuler.net/problem=60
// Prime pair sets

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <utility>

#include "../Shared/primes.h"

// Welp I kind of got bored of this question and looked up a solution, this one
// seems to boil down to brute force, the only subtlety is in setting up the
// iterations. Never look up another solution. There's no satisfaction in it.
// Go ahead and copy their solution for completions sake, 

using namespace std;

unsigned long long cat(unsigned long a, unsigned long b) {
	unsigned int n = 1;
	while(n < b)
		n *= 10;

	return a*n + b;
}

// Should key correspond to a prime number or its index?
map<unsigned int, set<unsigned int> > pairs;

int main(int argc, char* argv[]) {
	int N = primes.size();

	for(int i = 0; i < N; i++) {
		if (i % 100 == 0)
			printf("%d\n", i);
		pairs[i] = set<unsigned int>();
		pairs[i].insert(i);

		
		unsigned long pi = primes[i];
		for (int j = 0; j < i; j++) {
			unsigned long pj = primes[j];

			if (isPrime(cat(pi, pj)) && isPrime(cat(pj, pi)))
				pairs[j].insert(i);
		}
	}

	printf("\n\n");
	for (int i = 0; i < pairs.size(); i++) {
		if (pairs[i].empty())
			continue;

		bool debug = primes[i] == 5197 || primes[i] == 13;

		auto si = pairs[i];

		if (debug) {
			for (auto n : si)
				printf("%d ", primes[n]);
			printf("\n");
		}

		// Construct intersection between current set s and the sets that
		// correspond to the elements of s
		vector<unsigned int> inter(si.begin(), si.end());

		for (int j = 0; j < inter.size(); j++) {
			auto sj = pairs[inter[j]];

			auto it = set_intersection(inter.begin()+j, inter.end(), sj.begin(), sj.end(), inter.begin()+j);
			inter.resize(it - inter.begin());

			if (debug) {
				printf("intersect %d\n", primes[inter[j]]);
				for (auto n : inter)
					printf("%d ", primes[n]);
				printf("\n");
			}

			if (inter.size() < 5) {
				break;
			}
		}

		if(debug) {
			for (auto n : inter)
				printf("%d ", primes[n]);
			printf("\n");
		}

		if (debug)	getchar();

		if (inter.size() >= 4) {
			//getchar();
		}
	}

	auto set1 = pairs[1];
	auto set2 = pairs[3];
	vector<unsigned int> inter(max(set1.size(), set2.size()));

	auto it = set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inter.begin());
	inter.resize(it - inter.begin());

	printf("\n");
	printf("\n");
	printf("3 : ");
	for (auto i : set1)
		printf("%d ", primes[i]);
	printf("\n");

	printf("7 : ");
	for (auto i : set2)
		printf("%d ", primes[i]);
	printf("\n");
	printf("\n");
	printf("intersection of 3 and 7:\n");
	for (auto i : inter)
		printf("%d ", primes[i]);
	printf("\n");

	getchar();

	return 0;
}