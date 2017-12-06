// https://projecteuler.net/problem=63
// Powerful digit counts

#include <iostream>
#include <cmath>

using namespace std;

// 2ez

int main(int argc, char* argv[]) {
	const unsigned int N = 30;
	unsigned int count = 0;

	for (int i = 1; i < N; i++) {
		for (int j = 1; j < N; j++) {
			int digits = 1+(int)floor((double)j * log10((double)i));

			if (digits == j)
				count++;
		}
	}

	printf("count = %u\n", count);

	getchar();

	return 0;
}

