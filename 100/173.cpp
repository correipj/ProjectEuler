// https://projecteuler.net/problem=173
// Using up to one million tiles how many different "hollow" square laminae
// can be formed?

#include <iostream>

using namespace std;

typedef unsigned long long num_t;

int main(int argc, char* argv[]) {
	const num_t N = 1000000;

	num_t count = 0;

	for (num_t a = 1; 4*a*(a+1) <= N; a++)
		count += N/(4*a) - a;

	printf("count = %llu\n", count);

	getchar();

	return 0;
}
