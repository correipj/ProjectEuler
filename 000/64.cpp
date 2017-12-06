// https://projecteuler.net/problem=64
// Odd period square roots

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

unsigned int conFracSqrtPeriod(unsigned int n) {
	const double sqrtn = sqrt((double)n);

	int fracN = -floor(sqrtn);
	int fracD = 1;

	// perfect square
	if (n == fracN * fracN)
		return 0;

	printf("iter = %2d, fracN = %4d, fracD = %4d\n", 0, fracN, fracD);

	for (int iter = 1;; iter++) {
		fracD = (n - fracN*fracN)/fracD;
		fracN = -fracN;
		
		printf("calc = %.0f\n", -floor(((double)fracD - sqrtn - (double)fracN) / (double)fracD));
		int i = 0;

		while(sqrtn + (double)fracN > fracD) {
			i++;
			fracN -= fracD;
		}
		
		printf("expr = %d\n", i);
		
		if (fracN == -floor(sqrtn) && fracD == 1)
			return iter;
	}

	// Should never get here
	return 0;
}

int main(int argc, char* argv[]) {
	int nOdd = 0;

	conFracSqrtPeriod(7);
	getchar();
	
	for (int i = 2; i <= 10000; i++)
		nOdd += conFracSqrtPeriod(i) % 2;

	printf("%d odd periods\n", nOdd);

	getchar();

	return 0;
}

