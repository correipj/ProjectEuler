// https://projecteuler.net/problem=153
// Investigating Gaussian Integers

#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <map>
#include <utility>
#include "../Shared/primes.h"

using namespace std;

typedef unsigned long long num_t;

struct gaussint {
public:
	num_t a, b;

	gaussint() {
		a = 0; 
		b = 0;
	}
	gaussint(const num_t& A, const num_t& B) {
		a = A; 
		b = B;
	}
	gaussint(const gaussint& g) {
		a = g.a; 
		b = g.b;
	}	
	gaussint& operator=(const gaussint& g) {
		a = g.a; 
		b = g.b;

		return *this;
	}


	bool operator==(const gaussint& rhs) const {
		return a == rhs.a && b == rhs.b;
	}
	bool operator<(const gaussint& rhs) const {
		return (a*a + b*b) < (rhs.a*rhs.a + rhs.b*rhs.b);
	}
};


/*
for integers a, b > 0
(a^2 + b^2) = N
(a + bi) and (a - bi) divide N
(b + ai) and (b - ai) divide N

N may never == 3 (mod 4)

k(a+bi) divides N iff k(a^2+b^2) divides Na and Nb

k = {divisors of qa} union {divisors of qb}

qa = Na / (a^2 + b^2)
qb = Nb / (a^2 + b^2)


if a and b coprime, call (a + bi) a gaussian prime





*/

num_t gcd(num_t a, num_t b) {
	while(b) {
		num_t t = b;
		b = a % b;
		a = t;
	}
	return a;
}


bool myComp(const pair<num_t, num_t>& a, const pair<num_t, num_t>& b) {
	num_t sa = a.first*a.first + a.second*a.second;
	num_t ga = gcd(a.first, a.second);
	
	num_t sb = b.first*b.first + b.second*b.second;
	num_t gb = gcd(b.first, b.second);

	if (ga == gb)
		return a.second < b.second;

	return ga > gb;
	//return (sa/ga) < (sb/gb);
}

int main(int argc, char* argv[]) {
	const num_t lim = 100000;
	num_t sum = 0;

	for (num_t n = 1; n <= lim; n++) {
		sum += n * (lim / n);

		if (2*n <= lim)
			sum += 2*n*(lim/(2*n));
	}

	printf("0\n");
	for (num_t a = 1; 5*a <= lim; a++) {
		if (a % 1000 == 0)
			printf("%lld\n", a);

		set<num_t, greater<num_t> > divisors;

		// Compute divisors of a
		for (num_t i = 1; i <= sqrt(a); i++)
			if (a % i == 0) {
				divisors.insert(i);

				if (i != a/i)
					divisors.insert(a/i);
			}

		set<num_t> foundSums;

		for (auto d : divisors) {
			for (num_t b = a + d; a*a + b*b <= d*lim; b += d) {
				if (foundSums.count(b) == 1)
					continue;

				foundSums.insert(b);

				num_t s = a*a + b*b;
				num_t k = lim/(s/d);

				sum += 2*k*a;
				if (a != b)
					sum += 2*k*b;
			}
		}
	}

	printf("\n");
	printf("sum = %11lld\n", sum);
	printf("      00111222333\n");/**/
	
	getchar();

	return 0;
}
