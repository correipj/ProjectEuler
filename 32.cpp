// https://projecteuler.net/problem=32

#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

bool pandigital (int m1, int m2, int n) {
	if (n > 9876)
		return false;
	if (n < 1234)
		return false;

	vector<int> digit(10, 0);
	// Save LHS digits
	while(m1) {
		digit[m1%10] = 1;
		m1/= 10;
	}
	while(m2) {
		digit[m2%10] = 1;
		m2/= 10;
	}

	// Check RHS for duplicate digit
	while(n) {
		if (digit[n%10])
			return false;
		digit[n%10] = 1;
		n /= 10;
	}

	// Check RHS for missing digit
	for (int i = 1; i < digit.size(); i++)
		if (digit[i] == 0)
			return false;

	return true;
}

int main(int argc, char* argv[]) {
	vector<int> combo = { 0, 0, 0, 0, 1, 1, 1, 1, 1};
	vector<int> LHS;
	set<int> RHS;

	do {
		LHS.clear();
		for (int i = 0; i < combo.size(); i++)
			if (combo[i])
				LHS.push_back(i+1);

		do {			
			int m1 =              10*LHS[0] + LHS[1];
			int m2 = 100*LHS[2] + 10*LHS[3] + LHS[4];

			if (pandigital(m1, m2, m1*m2)) {
				printf("%d * %d = %d\n", m1, m2, m1 * m2);
				RHS.insert(m1 * m2);
			}

			m1 =                                        LHS[0];
			m2 = 1000*LHS[1] + 100*LHS[2] + 10*LHS[3] + LHS[4];


			if (pandigital(m1, m2, m1*m2)) {
				printf("%d * %d = %d\n", m1, m2, m1 * m2);
				RHS.insert(m1 * m2);
			}
		} while(next_permutation(LHS.begin(), LHS.end()));
	} while(next_permutation(combo.begin(), combo.end()));

	int sum = 0;
	for (auto i : RHS)
		sum += i;
	printf("sum = %d\n", sum);

	getchar();

	return 0;
}

