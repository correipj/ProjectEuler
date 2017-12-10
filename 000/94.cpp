// https://projecteuler.net/problem=94
// Almost equilateral triangles

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
	unsigned long long x, a, b;
	unsigned long long n, nSq;
	unsigned long long sum = 0;
	const unsigned long long lim = 1000000000;

	for (x = 3; x < lim; x += 2) {		
		if (3*x - 1 > lim)
			break;

		a = x;
		b = x - 1;
		nSq = 4*a*a - b*b;
		n = (unsigned long long)sqrt((double)nSq);

		if (n*n == nSq && b*n % 4 == 0)
			sum += 2*a + b;

		a = x;
		b = x + 1;
		nSq = 4*a*a - b*b;
		n = (unsigned long long)sqrt((double)nSq);

		if (n*n == nSq && b*n % 4 == 0)
			sum += 2*a + b;
	}

	printf("sum = %llu\n", sum);
	
	getchar();

	return 0;
}

