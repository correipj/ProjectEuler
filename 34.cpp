// https://projecteuler.net/problem=34

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

unsigned long long fact(unsigned long long n) {
	switch(n) {
	case 0:
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 6;
	case 4:
		return 24;
	case 5:
		return 120;
	case 6:
		return 720;
	case 7:
		return 5040;
	case 8:
		return 40320;
	case 9:
		return 362880;
	}

	return 1;
}

unsigned long long sumOfDigitFact(unsigned long long n) {
	unsigned long long sum = 0;

	while(n) {
		sum += fact(n % 10);
		n /= 10;
	}

	return sum;
}

int main(int argc, char* argv[]) {
	unsigned long long sum = 0;
	for (unsigned long long i = 10; i < 10000000; i++)
		if (i == sumOfDigitFact(i))
			sum += i;

	printf("sum = %llu\n", sum);

	getchar();

	return 0;
}

