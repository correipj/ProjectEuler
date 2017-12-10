// https://projecteuler.net/problem=93
// Arithmetic expressions

#include <iostream>
#include <array>
#include <set>
#include <cmath>

using namespace std;

typedef array<int, 4> digits_t;

double doOp(const double& a, const double& b, int op) {
	switch (op) {
	case 0:		return a + b;
	case 1:		return a - b;
	case 2:		return a * b;
	case 3:
		// Kind of hack-y but ez way to deal with div by 0
		if (b == 0.0)
			return 9999999.0;
		else
			return a / b;
	}
}

bool isInt(double d) {
	double intpart;

	// Don't compare to 0 just to make floating point math more forgiving
	// sometimes when divding and multiplying by 3 or 9 the result gets rounded
	// up or down causing the final answer to be off by about 1E-9
	return modf(d, &intpart) <= 0.0001;
}

unsigned int conSet(const digits_t& n) {
	set<double> res;
	double r;
	digits_t digs;

	// For every combination of operators
	for (int op1 = 0; op1 < 4; op1++)
		for (int op2 = 0; op2 < 4; op2++)
			for (int op3 = 0; op3 < 4; op3++) {
				digs = n;

				// Apply operators to every permutation of digits
				do {					
					// ((a x b) x c) x d
					r = doOp(doOp(doOp(digs[0], digs[1], op1), digs[2], op2), digs[3], op3);
					if (r > 0.0 && isInt(r))
						res.insert(r);

					// (a x b) x (c x d)					
					r = doOp(doOp(digs[0], digs[1], op1), doOp(digs[2], digs[3], op3), op2);
					if (r > 0.0 && isInt(r))
						res.insert(r);
				} while(next_permutation(digs.begin(), digs.end()));
			}

	// Find maximum consecutive number
	double i = 1;
	for (auto r : res) {
		if (i != r)
			return i-1;

		i++;
	}

	// All numbers are consecutive, just return last one
	return res.size()-1;
}

int main(int argc, char* argv[]) {
	digits_t maxDigits;
	unsigned int maxN = 0;

	for (int a = 1; a <= 9; a++)
		for (int b = a+1; b <= 9; b++)
			for (int c = b+1; c <= 9; c++)
				for (int d = c+1; d <= 9; d++) {
					digits_t dig = {a, b, c, d};

					unsigned int n = conSet(dig);

					if (n > maxN) {
						maxN = n;
						maxDigits = dig;
					}
				}

	printf("%d%d%d%d  =  %d\n", maxDigits[0], maxDigits[1], maxDigits[2], maxDigits[3], maxN);

	getchar();

	return 0;
}