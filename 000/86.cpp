// https://projecteuler.net/problem=86
// Cuboid route

#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

#define LIM 1818

// Ok so I mis-read the question and assumed it wanted the number of solutions
// when LIM = 10^6. This lead me to develop a much better algorithm than I had
// initially. Counting each individual solution rather than batching up each
// multiple of a fundamental pythagorean triple.

// Currently if you want to get the solution you need to increment LIM until
// the number solutions exceeds 1 million. Or just trust that I've already done
// this and determined the answer to be 1818.

struct trip {
	unsigned long long a, b, c;

	// Compare lexicographically
	bool operator< (const trip& rhs) const {
		if (a == rhs.a && b == rhs.b)
			return c < rhs.c;

		if (a == rhs.a)
			return b < rhs.b;

		return a < rhs.a;
	}
};

// return ordered triplet such that r.a <= r.b <= r.c
trip orderTrip(const trip& t) {
	trip r;

	r.a = min(t.a, min(t.b, t.c));
	r.b = max(min(t.a,t.b), min(max(t.a, t.b), t.c));
	r.c = max(t.a, max(t.b, t.c));

	return r;
}

unsigned long long countCuboids(const trip& t) {
	unsigned long long count = 0;

	// Test each muliplier k
	// test pyth triple (k*a)^2 + (k*b)^2 + (k*c)^2
	for (unsigned long long k = 1; k*t.b <= LIM && k*t.a <= 2*LIM; k++) {			
		// Count number of valid cuboids (x, y, z)
		// Through careful choice of x, y, z and smart limits, x <= y <= z
		unsigned long long incr = 0;
		if (k*t.a - 1 > k*t.b) {				
			const unsigned long long d = (k*t.a - 1) - k*t.b;
				
			if (d < k*t.a/2)
				incr = k*t.a/2 - d;
		} else
			incr = k*t.a/2;

		count += incr;
	}

	return count;
}

int main(int argc, char* argv[]) {
	// Create an array of fundamental pythagorean triplets a^2 + b^2 = c^2
	vector<trip> fundTrips;

	queue<trip> Q;
	Q.push({3, 4, 5});
	
	unsigned long long count = 0;

	while(!Q.empty()) {
		trip t = orderTrip(Q.front());
		Q.pop();
		
		// Don't add triplets that wont solve a shortest route of a cuboid with
		// sides of length <= lim
		if (t.a > LIM || t.b > 2*LIM)
			continue;
		
		count += countCuboids(t);
		swap(t.a, t.b);
		count += countCuboids(t);
				
		trip T;		
		T.a = -1*t.a + 2*t.b + 2*t.c;
		T.b = -2*t.a + 1*t.b + 2*t.c;
		T.c = -2*t.a + 2*t.b + 3*t.c;
		Q.push(T);

		T.a =  1*t.a + 2*t.b + 2*t.c;
		T.b =  2*t.a + 1*t.b + 2*t.c;
		T.c =  2*t.a + 2*t.b + 3*t.c;
		Q.push(T);

		T.a =  1*t.a - 2*t.b + 2*t.c;
		T.b =  2*t.a - 1*t.b + 2*t.c;
		T.c =  2*t.a - 2*t.b + 3*t.c;
		Q.push(T);
	}

	printf("N = %lu\n", LIM);
	printf("1000000\n");
	printf("%7llu cuboids\n", count);

	getchar();

	return 0;
}
