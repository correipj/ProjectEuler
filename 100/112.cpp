// https://projecteuler.net/problem=112
// Bouncy numbers

#include <iostream>

using namespace std;

typedef unsigned long long num_t;

bool bouncy(num_t n) {
	if (n < 100)
		return false;

	int lastD = n % 10;
	n /= 10;
	int currD = n % 10;
	n /= 10;

	bool incr = currD>lastD;
	bool decr = currD<lastD;

	while(n) {
		lastD = currD;
		currD = n%10;
		n /= 10;

		if (!incr && !decr) {
			incr = currD>lastD;
			decr = currD<lastD;
		}

		if (incr && currD < lastD)
			return true;
		if (decr && currD > lastD)
			return true;
	}

	return false;
}


// Careful when calling with d > numDigits(n)
// TODO: Replace pow(10, i) with a while loop and multiplication by 10
// in order to deal with large number problems
num_t nb(num_t n, unsigned int d) {
	if (d < 1)
		return bouncy(n);

	num_t top = n / pow(10, d);

	if (bouncy(top))
		return pow(10, d);

	num_t sum = 0;
	for (num_t i = 0; i < 10; i++)
		sum += nb((10*top + i) * pow(10, d-1), d-1);
	return sum;
}

num_t numBouncy(num_t n) {
	const unsigned int numDigits = 1+(unsigned int)log10((double)n);
	num_t sum = bouncy(n);

	num_t dOffset = 1;
	for (int i = 0; i < numDigits; i++) {
		while((n/dOffset) % 10) {
			n -= dOffset;
			sum += nb(n, i);
		}

		dOffset *= 10;
	}
	
	return sum;
}

num_t binSearch(num_t lower, num_t upper) {
	num_t mid = (lower + upper) / 2;

	num_t n = numBouncy(mid);
	double d = (double)n/(double)mid;

	if (d == 0.99)
		return mid;

	if (d > 0.99)
		return binSearch(lower, mid);
	else
		return binSearch(mid, upper);
}
	
int main(int argc, char* argv[]) {
	num_t last;
	num_t curr;
	for (curr = 100; ; curr *= 10) {
		num_t count = numBouncy(curr);

		double d = (double)count / (double)curr;

		if (d > 0.99)
			break;

		last = curr;
	}

	num_t num99 = binSearch(last, curr);

	printf("num99 = %llu\n", num99);

	getchar();

	return 0;
}
