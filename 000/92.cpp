// https://projecteuler.net/problem=92
// Square digit chains

#include <iostream>
#include <array>

using namespace std;

unsigned int sumOfDigitSquares(unsigned int num) {
	unsigned int sum = 0;
	while (num) {
		sum += (num % 10)*(num % 10);
		num /= 10;
	}
	return sum;
}

array<bool, 568> hit89; 

int main(int argc, char* argv[]) {
	hit89[0] = false;
	for (int i = 1; i < 568; i++) {
		hit89[i] = false;
		int n = i;

		do {
			n = sumOfDigitSquares(n);
		} while(n != 1 && n != 89);

		if (n == 89)
			hit89[i] = true;
	}

	int count = 0;
	for (unsigned int i = 1; i < 10000000; i++)
		count += hit89[sumOfDigitSquares(i)];
	
	printf("count = %d\n", count);

	getchar();

	return 0;
}

