// https://projecteuler.net/problem=117
// Red, green, and blue tiles

#include <iostream>
#include <map>

using namespace std;

typedef unsigned long long num_t;

map<unsigned int, num_t> filled;

num_t fill(unsigned int len) {
	if (filled[len])
		return filled[len];

	num_t sum = 0;
	for (int b = 1; b <= 4 && len >= b; b++) 
		sum += fill(len - b);

	return filled[len] = sum;
}


int main(int argc, char* argv[]) {	
	filled[0] = 1;
	filled[1] = 1;
	filled[2] = 2;
	
	printf("%llu\n", fill(50));
	
	getchar();

	return 0;
}
