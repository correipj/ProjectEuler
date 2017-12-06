// https://projecteuler.net/problem=100

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

double f(unsigned long long T) {
	return 0.5 + 0.5*sqrt(2*T*T - 2*T + 1);
}

int main(int argc, char* argv[]) {
	const unsigned long long Tmin = 1000000000000;

	// This problem boils down to diophantine equaions. Its pretty neat, you
	// can calculate the next solution as a linear function of the previous
	// solution

	unsigned long long b = 15;
	unsigned long long t = 21;

	while (t < Tmin) {
		unsigned long long oldB = b;
		unsigned long long oldT = t;

		b = 3*oldB + 2*oldT - 2;
		t = 4*oldB + 3*oldT - 3;
	}
	
	printf("%llu  blues\n%llu  total\n", b, t);
	getchar();

	return 0;
}
