// https://projecteuler.net/problem=206
// Concealed Square

#include <iostream>

using namespace std;

bool valid(unsigned long long n) {
	unsigned long long d = 10;

	while(n) {
		if ((n % 10) != (d % 10))
			return false;

		d--;
		n /= 100;
	}

	return true;
}

int main(int argc, char* argv[]) {
	const unsigned long long minSqrt = floor(sqrt(1020304050607080900));
	const unsigned long long maxSqrt =  ceil(sqrt(1929394959697989990));

	// Start from max since I know the answer is closer to max than min
	for (unsigned long long i = maxSqrt; i >= minSqrt; i--)
		if (valid(i*i)) {
			printf("i =  %llu\n", i);
			break;
		}
		
	getchar();

	return 0;
}
