// https://projecteuler.net/problem=56
// Powerful digit sum

#include <iostream>
#include <algorithm>
#include "BigIntegerLibrary.hh"

using namespace std;

unsigned long digitSum(const BigUnsigned& a) {
	string str = bigUnsignedToString(a);

	unsigned long sum = 0;

	for(auto c : str) {
		sum += c-'0';
	}

	return sum;
}

int main(int argc, char* argv[]) {
	unsigned long maxSum = 0;
	BigUnsigned pow;
	
	for (BigUnsigned a = 80; a < 100; a++) {
		cout << a << endl;
		pow = a*a;	// a^2
		pow *= pow;	// a^4
		pow *= pow;	// a^8
		pow *= pow;	// a^16
		pow *= pow;	// a^32
		pow *= pow;	// a^64

		for (BigUnsigned b = 65; b < 100; b++) {
			pow *= a;

			maxSum = max(maxSum, digitSum(pow));
		}
	}

	printf("max sum = %d\n", maxSum);

	getchar();

	return 0;
}
