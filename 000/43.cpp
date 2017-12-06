// https://projecteuler.net/problem=43
// Sub-string divisibility

#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

unsigned long long makeNumFromDigits(const array<int, 10> digits, unsigned char start = 0, unsigned char num = 10) {
	unsigned long long n = 0;
	for (int i = 0; i < num; i++) {
		n *= 10;
		n += digits[start+i];
	}
	return n;
}

int main(int argc, char* argv[]) {
	array<int, 10> digs = {1, 0, 2, 3, 4, 5, 6, 7, 8, 9};

	unsigned long long sum = 0;

	do {		
		int divis[7] = {2, 3, 5, 7, 11, 13, 17};
		bool allDivis = true;

		for (int j = 0; j < 7; j++)
			if (makeNumFromDigits(digs, j+1, 3) % divis[j]) {
				allDivis = false;
				break;
			}

		if (allDivis)
			sum += makeNumFromDigits(digs);
	} while(next_permutation(digs.begin(), digs.end()));

	printf("%llu\n", sum);

	getchar();

	return 0;
}

