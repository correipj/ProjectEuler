// https://projecteuler.net/problem=52
// Permuted multiples

#include <iostream>
#include <queue>
#include <map>

using namespace std;

int main(int argc, char* argv[]) {
	char buffer[32];
	string s0, s1;
	unsigned long long n;

	for (unsigned long long i = 1; i < 10000000; i++) {
		sprintf(buffer, "%llu", i);
		s0 = buffer;
		sort(s0.begin(), s0.end());

		bool sameDigits = true;
		for (unsigned long long j = 2; j <= 6; j++) {
			sprintf(buffer, "%llu", j*i);
			s1 = buffer;
			sort(s1.begin(), s1.end());

			if (s0 != s1) {
				sameDigits = false;
				break;
			}
		}

		if (sameDigits) {
			n = i;
			break;
		}
	}

	printf("n = %llu\n", n);

	getchar();

	return 0;
}

