// https://projecteuler.net/problem=99
// Largest exponential

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

struct be {
	be(unsigned long base=1, unsigned long exp=0) {
		b = base;
		e = exp;
	}

	bool operator<(const be& rhs) {
		return e*log(b) < rhs.e*log(rhs.b);
	}

	unsigned long b, e;
};

int main(int argc, char* argv[]) {
	ifstream fin("base_exp.txt");
	be maxBE;
	unsigned int maxN;
	unsigned int lineN = 1;

	while(fin.good()) {
		be newBE;
		char comma;
		fin >> newBE.b >> comma >> newBE.e;

		if (maxBE < newBE) {
			maxBE = newBE;
			maxN = lineN;
		}

		lineN++;
	}

	printf("%u\n", maxN);

	getchar();

	return 0;
}

