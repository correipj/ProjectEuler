// https://projecteuler.net/problem=55
// Lychrel numbers

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

#include "BigIntegerLibrary.hh"

using namespace std;

BigUnsigned palindrome(BigUnsigned n) {
	string s = bigUnsignedToString(n);
	reverse(s.begin(), s.end());
	return stringToBigUnsigned(s);
}

bool isPalindrome(BigUnsigned n) {
	string s1 = bigUnsignedToString(n);
	string s2(s1.rbegin(), s1.rend());

	return s1 == s2;
}

bool isLychrel(BigUnsigned n) {
	BigUnsigned p;

	for (int i = 1; i < 50; i++) {
		p = palindrome(n);
		
		n += p;

		if (isPalindrome(n))
			return false;
	}

	return true;
}

int main(int argc, char* argv[]) {
	unsigned int count = 0;

	for (BigUnsigned n = 1; n < 10000; n++)
		if (isLychrel(n))
			count++;

	printf("count = %d\n", count);

	getchar();

	return 0;
}

