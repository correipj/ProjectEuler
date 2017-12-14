// https://projecteuler.net/problem=115
// Counting block combinations II

#include <iostream>
#include <map>

using namespace std;

typedef unsigned long long num_t;

map<unsigned int, num_t> filled;

num_t fill(unsigned int len, unsigned int minB) {
	if (len < minB)
		filled[len] = 1;

	if (filled[len])
		return filled[len];

	// Can always fill len with one big block
	num_t sum = 1;
	for (int b = minB; b < len; b++)
		sum += fill(len - b - 1, minB);
	filled[len] = sum + fill(len-1, minB);

	return filled[len];
}

int main(int argc, char* argv[]) {	
	unsigned int n = 50;

	while(fill(++n , 50) < 1000000);

	printf("n = %d\n", n);

	getchar();

	return 0;
}
