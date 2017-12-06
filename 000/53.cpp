// https://projecteuler.net/problem=53
// Combinatoric selections

#include <iostream>

using namespace std;

unsigned int count(unsigned int n) {
	if (n < 23)
		return 0;

	unsigned int ret = 1;
	unsigned int prod = 1;
	
	for (int i = 1; i < n; i++) {
		prod *= n-i+1;
		prod /= i;
		
		if (prod > 1000000)
			break;
		
		ret += 2;
	}

	return n - ret;
}

int main(int argc, char* argv[]) {
	unsigned int sum = 0;
	for (int i = 1; i <= 100; i++) 
		sum += count(i);

	printf("sum = %d\n", sum);

	getchar();

	return 0;
}

