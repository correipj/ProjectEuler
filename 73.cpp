// https://projecteuler.net/problem=73
// Counting fractions in a range

#include <iostream>
#include <vector>
#include "../Shared/primes.h"

using namespace std;

struct frac {
public:
	typedef unsigned long long T;
	T n, d;

	frac() {
		n = 0;
		d = 1;
	}
	frac(const frac& f) {
		n = f.n;
		d = f.d;
	}
	frac(T n_, T d_) {
		n = n_;
		d = d_;
	}

	frac& operator=(const frac& f) {
		n = f.n;
		d = f.d;
		return *this;
	}
	
	bool operator<(const frac& rhs) const {
		return n * rhs.d < rhs.n * d;
	}
	bool operator>(const frac& rhs) const {
		return n * rhs.d > rhs.n * d;
	}
};



int main(int argc, char* argv[]) {
	unsigned int count = 0;

	for (int d = 4; d <= 12000; d++) {
		if (d % 1000 == 0)
			printf("%d\n", d);

		const unsigned int minN =  ceil((double)d/3.0);
		const unsigned int maxN = floor((double)d/2.0);


		vector<int> coprime(maxN+1, 1);

		for (auto p : primes) {
			if (p > maxN)
				break;

			if (d % p)
				continue;
			
			for (int i = 0; i < coprime.size(); i += p)
				coprime[i] = 0;
		}

		for (int i = minN; i <= maxN; i++)
			count += coprime[i];
	}
	
	printf("count = %d\n", count);
	
	getchar();

	return 0;
}

