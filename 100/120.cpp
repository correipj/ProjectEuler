// https://projecteuler.net/problem=120
// Square remainders

#include <iostream>

using namespace std;

typedef unsigned long long num_t;

/* 
After some algebra, I determined the remainder to be
r = 2				when n is even
r = 2*n*a mod a^2	when n is odd

find max r as n varies of 
2*n*a = a^2*k + r
where n and k are integers

r = a*(2*n - a*k) = a*b, b is integer
therefor r has to be some integer multiple of a

through experimentation I find

b = 2*floor((a-1)/2)

r = a*b

*/

int main(int argc, char* argv[]) {
	num_t sum = 0;
	for (num_t a = 3; a <= 1000; a++)
		sum +=  2*a*((a-1)/2);

	printf("sum = %llu\n", sum);
	
	getchar();

	return 0;
}
