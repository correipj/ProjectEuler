// https://projecteuler.net/problem=85
// Counting rectangles

#include <iostream>

using namespace std;

unsigned long choose2(unsigned int a) {
	return a*(a-1)/2;
}

unsigned long f(unsigned int a, unsigned int b) {
	return choose2(a+1) * choose2(b+1);
}


int main(int argc, char* argv[]) {
	unsigned long minError = 99999999;
	unsigned long area;

	for (int i = 30; i < 100; i++)
		for (int j = 1; j < 100; j++) {
			unsigned long error = abs(2000000-(long)f(i, j));

			if (error < minError) {
				minError = error;
				area = i*j;
			}
		}

	printf("area = %d\n", area);

	getchar();
	
	return 0;
}

