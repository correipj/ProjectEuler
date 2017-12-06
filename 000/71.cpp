// https://projecteuler.net/problem=71
// Ordered fractions


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
	frac maxFrac;
	frac thresh(3,7);
	
	for (int n = 2; n <= 10000000; n++) {
		frac f(n*3/7, n);

		if (f < thresh && f > maxFrac)
			maxFrac = f;
	}

	printf("maxFrac = %8llu / %8llu\n", maxFrac.n, maxFrac.d);
	
	getchar();

	return 0;
}

