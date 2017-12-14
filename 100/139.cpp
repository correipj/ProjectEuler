// https://projecteuler.net/problem=139
// Pythagorean tiles

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

typedef unsigned long num_t;

struct trip {
	num_t a, b, c;
};


int main(int argc, char* argv[]) {
	const num_t perimLim = 100000000;

	queue<trip> Q;
	Q.push({3, 4, 5});

	unsigned long count = 0;

	while(!Q.empty()) {
		trip t = Q.front();
		Q.pop();

		const num_t perim = t.a + t.b + t.c;

		if (perim >= perimLim)
			continue;
		
		if (t.c % (max(t.a, t.b) - min(t.a, t.b)) == 0)
			count += perimLim / perim;

		trip T;		
		T.a = 1*t.a + 2*t.b + 2*t.c;
		T.b = 2*t.a + 1*t.b + 2*t.c;
		T.c = 2*t.a + 2*t.b + 3*t.c;
		Q.push(T);
	}

	printf("count = %lu\n", count);
	
	getchar();

	return 0;
}
