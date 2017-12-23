// https://projecteuler.net/problem=210
// Obtuse Angled Triangles

#include <iostream>

using namespace std;

typedef unsigned long long num_t;

// # of lattice points inside but not on the circle defined by
// (x - n/8)^2 + (y - n/8)^2 = 2(n/8)^2
// Not including lattice points where x=y
// See: https://en.wikipedia.org/wiki/Gauss_circle_problem
// Note that this is for a circle centered at (0,0)
// See: http://mathworld.wolfram.com/CircleLatticePoints.html
num_t latticeInCircle(num_t n) {
	// Gauss circle function
	/*num_t sum = 1;
	num_t nSq = n;

	for (num_t i = 0; 4*i+1 <= nSq; i++)
		sum += 4*((nSq / (4*i+1)) - (nSq / (4*i+3)));

	return sum;*/
	
	// Manually count each point
	// Can be sped up by a factor of 2 with almost no work and by a factor of
	// 4 with more work. However brute force is not the way to approach this
	// part of the problem
	const double dn = (double)n;
	const double minX = dn*(1.0 - sqrt(2))/8.0;
	const double maxX = dn*(1.0 + sqrt(2))/8.0;

	const double radSq = dn*dn/32.0;

	num_t count = 0;
	
	// Perhaps inner for-loop could be solved ananlytically to change this
	// into an O(n) problem instead of O(n^2)
	for (double x = floor(minX); x < maxX; x++) {
		const double dx = dn/8.0 - x;

		const double sqrtNX = sqrt(dn*dn/64.0 + dn*x/4.0 - x*x);
		const double minY = n/8.0 - sqrtNX;
		const double maxY = n/8.0 + sqrtNX;

		for (double y = floor(minY); y < maxY; y++) {
			const double dy = dn/8.0 - y;
			
			if (/*x != y && */dx*dx + dy*dy < radSq)
				count++;
		}
	}

	return count;
}

num_t count(num_t n) {
	num_t totalPts = (n+1)*(n+1) + n*n;

	num_t diagPts = n + 1 - (n % 2);
	
	num_t A = n+1 - (n%2);
	num_t B = n+0 + (n%2);
	num_t n1 = (n+4)/4;
	num_t n2 = (n+2)/4;
	num_t rangePts = A*n1 + B*n2;
	
	// Intersection of RangePts and DiagPts, counted twice so add back in
	num_t rangeDiagPts = n1;

	// Extra class of pts, second smaller range
	// # of lattice points inside but not on the circle defined by
	// (x - n/8)^2 + (y - n/8)^2 = 2(n/8)^2
	//  points x=y are to be excluded
	// This number of points should be added to our sum

	return totalPts - diagPts - rangePts + rangeDiagPts + latticeInCircle(n);
}

int main(int argc, char* argv[]) {
	for (num_t i = 4; i <= 20; i++) {
		printf("%10lld   %20lld\n", i, latticeInCircle(i));
		printf("%10lld   %20lld\n", 4*i, latticeInCircle(4*i));
		printf("\n");
	}
	getchar();

	return 0;
}
