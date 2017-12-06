// https://projecteuler.net/problem=65
// Convergents of e

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

class BigInt {
public:
	BigInt() {}
	BigInt(unsigned int n) {
		while(n) {
			d.push_back(n % 10);
			n /= 10;
		}
	}
	BigInt(const BigInt& b) {
		d = b.d;
	}
	BigInt& operator=(const BigInt& b) {
		d = b.d;
		return *this;
	}

	BigInt& operator+=(const BigInt& b) {
		unsigned char carry = 0;

		while(b.d.size() > d.size())
			d.push_back(0);

		int digits = min(d.size(), b.d.size());
		int i;
		for (i = 0; i < digits; i++) {
			d[i] += b.d[i] + carry;
			carry = d[i] > 9;
			d[i] = d[i] % 10;
		}

		if (carry)
			if (i < d.size())
				d[i] += carry;
			else
				d.push_back(carry);

		return *this;
	}

	BigInt operator+(const BigInt& b) const {
		BigInt R(*this);
		R += b;
		return R;
	}

	BigInt& operator*=(const unsigned int& n) {
		if (n == 10) {
			d.insert(d.begin(), 0);
			return *this;
		}

		if (n < 10) {
			unsigned char carry = 0;
			for (int i = 0; i < d.size(); i++) {
				d[i] = d[i] * n + carry;
				carry = d[i] / 10;
				d[i] = d[i] % 10;
			}

			if (carry)
				d.push_back(carry);

			return *this;
		}

		int num = n;
		BigInt sum;
		int digit = 0;
		while(num) {
			int m = num%10;

			BigInt prod = (*this)*m;
			for (int i = 0; i < digit; i++)
				prod *= 10;
			digit++;

			sum += prod;

			num /= 10;
		}

		d = sum.d;

		return *this;
	}

	BigInt operator*(const unsigned int& n) const {
		BigInt R(*this);
		R *= n;
		return R;
	}

	void print() {
		for (int i = d.size()-1; i >= 0; i--)
			printf("%d", d[i]);
	}

	vector<unsigned char> d;
};

unsigned int sumOfDigits(unsigned long long n) {
	int sum = 0;
	while (n) {
		sum += n % 10;
		n /= 10;
	}
	return sum;
}

int main(int argc, char* argv[]) {
	int N = 100;
	BigInt num = 1;
	BigInt den = (N%3 == 0)?2*(N/3):1;

	for (int iter = N-1; iter > 1; iter--) {
		int seq = (iter%3 == 0)?2*(iter/3):1;

		// Add num in sequence
		num += den * seq;

		// Inverse
		swap(num, den);
	}
	
	// Add Two
	num += den * 2;

	num.print();
	printf(" / ");
	den.print();
	printf("\n");

	int sum = 0;
	for (int i = 0; i < num.d.size(); i++)
		sum += num.d[i];

	printf("sum = %d\n", sum);

	getchar();

	return 0;
}

