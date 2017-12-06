// https://projecteuler.net/problem=40
// Champernowne's constant

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<unsigned int> seq;

// digitN(1357, 0) == 1
// digitN(1357, 1) == 2
// digitN(1357, 2) == 3
// digitN(1357, 3) == 4
unsigned int digitN(unsigned int n, unsigned int d) {
	int totDigit = 0;
	int a = 1;

	while(a <= n) {
		totDigit++;
		a *= 10;
	}

	d = totDigit-d;
	while(--d)
		n /= 10;
	
	return n % 10;
}

unsigned int fracN(unsigned int n) {
	int d = 0;
	while(n >= seq[++d]);

	n -= seq[d-1];

	return digitN(pow(10, d-1) + n/d, n % d);
}

int main(int argc, char* argv[]) {
	// seq[2] = 190
	// seq[3] = 2890
	// ex. let i = index, 190 <= i < 2890, number at index i must be a part of
	// a 3 digit number.
	// This sequence could be calculated inside the fracN function to avoid the
	// use of a global variable but whatever.
	unsigned int sum = 1;
	seq.push_back(1);
	for (int i = 1; i < 9; i++)
		seq.push_back(seq.back() + i*9*pow(10,i-1));

	unsigned int prod = 1;
	for (int i = 1; i <= 1000000; i *= 10)
		prod *= fracN(i);

	printf("prod = %u\n", prod);

	getchar();

	return 0;
}
