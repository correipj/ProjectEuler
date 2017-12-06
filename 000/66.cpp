// https://projecteuler.net/problem=66
// Diophantine equation

#include <iostream>
#include <algorithm>
#include <vector>
#include "BigIntegerLibrary.hh"

using namespace std;

// See algorithm described in 
// http://mathworld.wolfram.com/PellEquation.html
BigUnsigned pell(unsigned int d) {
	const double sqrtd = sqrt((double)d);
	BigUnsigned a0 = (unsigned long)floor(sqrtd);

	// perfect square
	if ((BigUnsigned)d == a0 * a0)
		return 1;

	BigUnsigned pLast = 1;
	BigUnsigned pCurr = a0;
	BigUnsigned qLast = 0;
	BigUnsigned qCurr = 1;
	
	BigUnsigned PLast = 0;
	BigUnsigned PCurr = 0;
	BigUnsigned QLast = 1;
	BigUnsigned QCurr = 1;

	BigUnsigned a = a0;
	BigUnsigned oldp, oldq, oldP, oldQ;

	for (int iter = 1;; iter++) {
		oldP = PCurr;
		PCurr = a * QCurr - oldP;
		PLast = oldP;

		oldQ = QCurr;
		QCurr = ((BigUnsigned)d - PCurr*PCurr)/oldQ;
		QLast = oldQ;

		a = (a0 + PCurr) / QCurr;

		oldp = pCurr;
		pCurr = a*pCurr + pLast;
		pLast = oldp;

		oldq = qCurr;
		qCurr = a*qCurr + qLast;
		qLast = oldq;

		if (a == a0*2 && iter % 2 == 0)
			return pLast;
	}
}

int main(int argc, char* argv[]) {
	BigUnsigned maxX = 0;
	int d;
	
	for (int i = 2; i <= 1000; i++) {
		BigUnsigned x = pell(i);

		if (x != 1) {
			if(x > maxX){
				maxX = x;
				d = i;
			}
		}
	}

	cout << "max = " << d << endl;

	getchar();

	return 0;
}

