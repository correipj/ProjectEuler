// https://projecteuler.net/problem=38
// Pandigital multiples

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

#define MIN_PAN	123456789
#define MAX_PAN 987654321

int catProd (unsigned int n, unsigned int k) {
	int sum = 0;

	for (int i = 1; i <= k; i++) {
		sum *= pow(10, 1+(int)log10(n*i));
		sum += n*i;
	}

	return sum;
}

bool pandigital(unsigned int n) {
	if (n > MAX_PAN)
		return false;
	if (n < MIN_PAN)
		return false;

	vector<int> digits (10, 0);

	while (n) {	
		if (n % 10 == 0)		// Zeros aren't allowed
			return false;		//
		if (digits[n % 10]++)	// Check for repeated digits while
			return false;		// saving current digits
			
		n /= 10;
	}

	// Check for missing digits (excluding 0)
	for (int i = 1; i < digits.size(); i++)
		if (digits[i] == 0)
			return false;

	return true;
}

int main(int argc, char* argv[]) {
	int maxN, maxK, maxP = 0;
	int n = 9;
	bool quit = false;
	while (!quit) {
		for (int k = 2; k < 9; k++) {
			int prod = catProd(n, k);

			if (prod > MAX_PAN) {
				if (k == 2) 
					quit = true;
				continue;
			}

			if (pandigital(prod) && prod > maxP) {
				maxN = n;
				maxK = k;
				maxP = prod;
			}
		}
		n++;
	}

	printf("%d * (1 .. %d) = %d\n", maxN, maxK, maxP);

	getchar();

	return 0;
}

