// https://projecteuler.net/problem=613

#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include <vector>

//#define PI	3.14159265359

using namespace std;


// Ok so this problem seems to just be a double integral. The only complication
// is that the final answer needs to be correct to 10 decimal places. Euler
// integration is painfully slow, taking about a minute for 4-5 decimal places
// I could try other higher order integration methods, especially those meant
// for 2 dimensional areas of integration but my intuition tells me I should
// be able to simplify this to a 1D integration problem. integrand is just a 
// difference of arctans. It isn't impossible to integrate by hand, just really
// long. I could solve what is easy and let the computer solve the higher order
// parts but this might run into the same problems as before.


double f(double x, double y) {
	return M_PI - atan2(4-x, y) - atan2(3-y, x);
}

double integrate(double(*func)(double), double a, double b, unsigned long n) {
	double sum = 0.0;

	const double dx = (b - a) / (double)n;
	for (double x = a; x < b; x += dx)
		sum += func(x + 0.5*dx) * dx;
	
	return sum;
}


int main(int argc, char* argv[]) {
	vector<unsigned int> testNs = {100, 500, 1000, 5000, 10000, 20000, 30000, 40000, 50000};
	
	for (auto n : testNs) {
		const double minX = 0.0;
		const double maxX = 4.0;
		const double dx = (maxX - minX) / (double)n;
		double sum = 0.0;

		for (double x = minX; x < maxX; x += dx) {
			const double minY = 0.0;
			const double maxY = 3 - 0.75*x;
			const double dy = (maxY - minY) / (double)n;
			double sumY = 0.0;
				
			for (double y = minY; y < maxY; y += dy)
				sumY += f(x, y) * dy;

			sum += sumY * dx;
		}
		printf("N = %5d   %.9f\n", n, sum/(1*2*M_PI));
	}
	
	getchar();

	return 0;
}