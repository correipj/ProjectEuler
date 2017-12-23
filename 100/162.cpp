// https://projecteuler.net/problem=162
// Hexadecimal numbers

#include <iostream>

using namespace std;

typedef unsigned long long num_t;


// Count how many d-digit hex numbers contain a specific digit value
num_t count1(num_t d) {
	if (d < 1)
		return 0;
	//printf("count1(%d)\n", d);

	num_t sum = 0;

	sum += (num_t)1 << (4*(d-1));
	sum += 15*count1(d-1);

	return sum;
}

// Count how many d-digit hex numbers contain a non-leading 0
num_t count0(num_t d) {
	if (d < 1)
		return 0;

	num_t sum = 0;

	sum += 15*count1(d-1);
	sum +=  1*count0(d-1);

	return sum;
}



num_t count2(num_t d) {
	if (d < 2)
		return 0;

	num_t sum = 0;

	sum += 14*count2(d-1);
	sum +=  2*count1(d-1);

	return sum;
}

num_t count01(num_t d) {
	if (d < 2)
		return 0;

	num_t sum = 0;
	sum += count01(d-1);
	sum += count1(d-1);
	sum += 14*count2(d-1);

	return sum;
}

num_t count3(num_t d) {
	if (d < 3)
		return 0;

	num_t sum = 0;
	sum += 13*count3(d-1);
	sum +=  3*count2(d-1);

	return sum;
}

num_t count02(num_t d) {
	if (d < 3)
		return 0;

	num_t sum = 0;
	sum += count02(d-1);
	sum += 2*count2(d-1);
	sum += 13*count3(d-1);

	return sum;
}

int main(int argc, char* argv[]) {
	for (num_t d = 0; d <= 16; d++)
		printf("%2lld  %llX\n", d, count02(d));

	
	getchar();

	return 0;
}
