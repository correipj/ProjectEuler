// https://projecteuler.net/problem=122
// Efficient exponentiation

#include <iostream>
#include <vector>
#include <map>
#include "../Shared/primes.h"

using namespace std;

typedef vector<unsigned int> powers_t;

class comp {
	unsigned int N;
public:
	comp(unsigned int n) {
		N = n;
	}


	bool operator() (const powers_t& a, const powers_t& b) {
		// Smallest set gets highest priority
		if (a.size() == b.size())
			//return lexicographical_compare(a.rbegin(), a.rend(), b.rbegin(), b.rend());
			return *a.rbegin() > *b.rbegin();
		
		return a.size() < b.size();
	
		/*unsigned int sumRA = 0;
		unsigned int sumRB = 0;
		
		for (auto x : a)
			sumRA += N % x;

		for (auto x : b)
			sumRB += N % x;

		return sumRA < sumRB;*/
	}
};

unsigned int minExpGreedy(unsigned int n, powers_t p) {
	unsigned int iters = 0;	
	unsigned int g = p.back();

	for (int i = p.size()-1; i >= 0; i--)
		if (p[i] + g <= n) {
			//printf("%d + %d = %d\n", g, p[i], g + p[i]);
			g += p[i];
			iters++;
		}

	return iters;
}

map<unsigned int, unsigned int> minLen;

unsigned int minExp(unsigned int n) {
	if (n == 1)
		return 0;
	
	powers_t init;
	init.push_back(1);

	// This can be a list, don't need random access, just for debugging
	vector<powers_t> Q;
	Q.push_back(init);

	unsigned int iters = 0;

	unsigned int minE = 9999;

	comp comparator(n);


	while(!Q.empty()) {
		iters++;
		
		auto it = min_element(Q.begin(), Q.end(), comparator);
		powers_t p = *it;
		Q.erase(it);

		if (p.size() >= minE)
			break;
		
		unsigned int g = p.back();
		if (2*g > n) {
			auto greedy = minExpGreedy(n, p);
			
			minE = min(minE, p.size() + greedy - 1);

			continue;
		}

		for (auto x : p) {
			if (x + g == n)
				return p.size();

			if (x + g > n)
				break;
			
			powers_t newP(p);
			newP.push_back(x+g);

			// Only push newP if it is the minimum length set ending with g
			// ie if (1,2,4) was already calculated, dont push (1,2,3,4)

			// Equal length is valid
			// ex if (1,2,4,8,12) was calculated, still push (1,2,3,6,12)

			if (minLen[x+g] == 0 || minLen[x+g] >= newP.size()) {
				minLen[x+g] = newP.size();
				Q.push_back(newP);
			}
		}

		//sort(Q.begin(), Q.end(), comparator);
	}

	return minE;
}

#include <ctime>

/*
Slowest damned solution I've ever done

Most on the forums used brute force, but a few found a solution that runs
in under a second or so.

*/

int main(int argc, char* argv[]) {
	clock_t t1 = clock();

	unsigned int sum = 0;
	for (int i = 1; i <= 200; i++) {
		auto minE = minExp(i);

		printf("minExp(%3d) = %d\n", i, minE);

		sum += minE;
	}
	clock_t t2 = clock();

	printf("runtime = %.2fs\n", (float)(t2 - t1)/(float)CLOCKS_PER_SEC);

	printf("sum = %u\n", sum);
	
	getchar();

	return 0;
}
