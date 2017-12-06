// https://projecteuler.net/problem=33
// Digit cancelling fractions

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int cancel(int a, int b) {
	if (a == b)
		return 0;

	double frac = (double)a/b;
	int da1 = (a/10)%10;
	int da2 = a%10;
	int db1 = (b/10)%10;
	int db2 = b%10;

	if (da2 == 0 || db2 == 0)
		return 0;

	if (da1 == db2 && frac == (double)da2/db1)
		return 1;
	if (da2 == db2 && frac == (double)da1/db1)
		return 1;
	if (da1 == db1 && frac == (double)da2/db2)
		return 1;
	if (da2 == db1 && frac == (double)da1/db2)
		return 1;

	return 0;
}


int main(int argc, char* argv[]) {
	unsigned long pa = 1;
	unsigned long pb = 1;
	for (int a = 10; a < 100; a++)
		for (int b = a; b < 100; b++) {
			if(cancel(a, b)) {
				pa *= a;
				pb *= b;
				printf("a = %d, b = %d\n", a, b);
			}
		}		
	
	// Cancel via inspection, find denominator = 100
	printf("pa = %lu\n", pa);
	printf("pb = %lu\n", pb);

	getchar();

	return 0;
}

