// https://projecteuler.net/problem=80
// Square root digital expansion

#include <iostream>
#include <fstream>
#include <vector>
#include "../BigInt/BigIntegerLibrary.hh"

using namespace std;

// http://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Decimal_(base_10)
unsigned int sqrtDigitSum(unsigned int n) {	
	BigUnsigned p = 0;
	BigUnsigned c;
	if (n >= 100)
		c = n / 100;
	else
		c = n;

	unsigned int sum = 0;

	for (int i = 0; i < 100; i++){
		unsigned int x = 0;
		while((BigUnsigned)(x+1)*(p*20 + x + 1) <= c)
			x++;

		c -= (BigUnsigned)x*(p*20 + x);
		c *= 100;

		if (i == 0 && n >= 100)
			c += n % 100;

		sum += x;

		p = p * 10 + x;
	}

	return sum;
}

int main(int argc, char* argv[]) {
	vector<int> perfectSquares;
	for (int i = 1; i < 13; i++)
		perfectSquares.push_back(i*i);

	unsigned long sum = 0;
	
	for (int i = 1; i <= 100; i++) {
		if (find(perfectSquares.begin(), perfectSquares.end(), i) != perfectSquares.end())
			continue;

		sum += sqrtDigitSum(i);
	}

	printf("sum = %lu\n", sum);
	
	getchar();

	return 0;
}

