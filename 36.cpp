// https://projecteuler.net/problem=36

#include <iostream>
#include <vector>

using namespace std;


vector<int> base(int n, int b) {
	vector<int> v;

	while(n) {
		v.insert(v.begin(), n % b);
		n /= b;
	}

	return v;
}

bool isPalindrome(int n, int b) {
	int rev = 0;

	for (int k = n; k > 0; k /= b)
		rev = rev * b + k % b;

	return n == rev;
}

int main(int argc, char* argv[]) {
	unsigned long sum = 0;
	for (int n = 1; n < 1000000; n += 2) {		
		if (!isPalindrome(n, 2))
			continue;
		if (!isPalindrome(n, 10))
			continue;

		sum += n;
	}

	printf("sum = %d\n", sum);

	getchar();

	return 0;
}