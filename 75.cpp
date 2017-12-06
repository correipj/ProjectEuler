// https://projecteuler.net/problem=75
// Singular integer right triangles

#include <iostream>
#include <queue>
#include <map>

using namespace std;

struct trip {
	unsigned long a, b, c;
};

map<unsigned long, int> tripCount;

int main(int argc, char* argv[]) {
	const unsigned long lim = 1500000;

	queue<trip> Q;
	trip init;
	init.a = 3;
	init.b = 4;
	init.c = 5;
	Q.push(init);

	while(!Q.empty()) {
		trip t = Q.front();
		Q.pop();

		const unsigned long sum = t.a + t.b + t.c;
		unsigned long n = 0;

		do {
			n += sum;

			tripCount[n]++;
		} while(n+sum <= lim);


		trip T;		
		T.a = -1*t.a + 2*t.b + 2*t.c;
		T.b = -2*t.a + 1*t.b + 2*t.c;
		T.c = -2*t.a + 2*t.b + 3*t.c;

		if (T.a + T.b + T.c <= lim)
			Q.push(T);

		T.a =  1*t.a + 2*t.b + 2*t.c;
		T.b =  2*t.a + 1*t.b + 2*t.c;
		T.c =  2*t.a + 2*t.b + 3*t.c;
		
		if (T.a + T.b + T.c <= lim)
			Q.push(T);

		T.a =  1*t.a - 2*t.b + 2*t.c;
		T.b =  2*t.a - 1*t.b + 2*t.c;
		T.c =  2*t.a - 2*t.b + 3*t.c;

		if (T.a + T.b + T.c <= lim)
			Q.push(T);
	}

	
	unsigned long count = 0;
	for (auto a : tripCount)
		if (a.second == 1)
			count++;

	printf("count = %lu\n", count);

	getchar();

	return 0;
}

