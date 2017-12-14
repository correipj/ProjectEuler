// https://projecteuler.net/problem=114
// Counting block combinations I

#include <iostream>
#include <map>

using namespace std;

typedef unsigned long long num_t;

map<unsigned int, num_t> filled;

num_t fill(unsigned int len) {
	if (filled[len])
		return filled[len];

	// Can always fill len with one big block
	num_t sum = 1;
	for (int b = 3; b < len; b++)
		sum += fill(len - b - 1);
	filled[len] = sum + fill(len-1);

	return filled[len];
}


int main(int argc, char* argv[]) {	
	filled[0] = 1;
	filled[1] = 1;
	filled[2] = 1;
	filled[3] = 2;
	
	printf("%llu\n", fill(50));
	
	getchar();

	return 0;
}
