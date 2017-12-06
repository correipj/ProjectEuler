// https://projecteuler.net/problem=57
// Square root convergents

#include <iostream>

using namespace std;

// Recurrance formula given in
// https://en.wikipedia.org/wiki/Square_root_of_2#Continued_fraction_representation
// Only iterations that produce longer numerator come after 7 iterations
// then after 4, then after 7 ... etc. 
int main(int argc, char* argv[]) {
	unsigned int count = 0;
	
	for (int iter = 1; iter <= 1000; iter++)
		if (iter % 13 == 0 || iter % 13 == 8)
			count++;

	printf("count = %d\n", count);
	
	getchar();

	return 0;
}

