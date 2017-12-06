// https://projecteuler.net/problem=243

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

// Look into primorial numbers, what does it mean for a number to be coprime to
// a number like 2*3*5*7*9*11*13 = 30030
// Probably has to decompose to primes greater than 13
// Can we count this quicker than 1 by 1? Cant just go through all primes since
// 17*19 = 323 is coprime to 30030

const vector<unsigned int> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,
67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,
173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,
277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,
397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,
509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,
641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,
761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,
887,907,911,919,929,937,941,947,953,967,971,977,983,991,997}; 

bool isPrime(unsigned long n) {
	if (n < 2)
		return false;

	const unsigned long lim = ceil(sqrt(n));

	for (auto p : primes) {
		if (p > lim)
			break;

		if (n % p == 0)
			return false;
	}

	return true;
}

void printPrimeFactorization(FILE* f, unsigned long long n) {
	const unsigned int lim = ceil(sqrt(n));
	for (int p = 0; n > 1 && p < primes.size(); p++) {
		if (primes[p] > lim)
			break;

		int count = 0;
		while(n % primes[p] == 0) {
			n /= primes[p];
			count++;
		}

		if (count) {
			if (p)	fprintf(f, " * ");		
			fprintf(f, "%d", primes[p]);
			if (count > 1) fprintf(f, "^%d", count);
		}
	}
}

// k is number of prime factors in n. ex:
// k = 1  ->  n = A*2*3
// k = 2  ->  n = A*2*3*5
// k = 3  ->  n = A*2*3*5*7

// New approach:
// Use 2*3*5*7 = 210 as example.
// Instead of iterating through 1..209, count resiliant fractions arithmatically
// 0. Start with count = n = 210-1. These are the total number of fractionsto consider.
// 1. Count factors of 2, 3, 5 and 7. These are fractions that will reduce so
//		they should be subtracted from the count
// 2. Count factors of 2*3, 2*5 ... etc. These are numbers that were counted
//		twice in step one and should be added back to count
// 3. Count factors of 2*3*5, 2*3*7 ... etc. These are numbers that were three
//		times in total, they should not have been added to the count in step 2,
//		subtract these from the count
// 4. Done.
//
// To count factors of a*b, take floor(209 / a*b). Addition / subtraction operaton
// alternates as number of prime factors in divisor increases. ie 1 = sub, 2 = add,
// 3 = sub ...etc
// I'm pretty sure you can get away with this approach for any number, just taking
// a list of its prime factors as the basis

double res (unsigned long long n) {
	if (isPrime(n))
		return 1.0;

	// Find prime factors
	vector<int> primeFac;
	const unsigned long long pLim = ceil(sqrt(n));

	for (int p = 0; p < primes.size(); p++) {
		if (primes[p] > pLim)
			break;

		if (n % primes[p] == 0)
			primeFac.push_back(primes[p]);
	}

	// Create vector of 0s and 1s of of total length equal to number of prime
	// factors. 1s correspond to primes included in count. ex 0 1 0 0 1 means
	// check for multiples of 3*11.
	vector<int> primeIndex(primeFac.size(), 0);
	primeIndex.back() = 1;

	long long count = (long long)(n - 1);

	for (int numFacs = 1; numFacs <= primeFac.size(); numFacs++) {
		// check all permutations of this binary vector, 
		// count number of multiples corresponding to each pemutation.
		do {
			unsigned long long factor = 1;
			for (int f = 0; f < primeIndex.size(); f++)
				if (primeIndex[f])
					factor *= primeFac[f];

			// Alternate adding or subtracting these counts based on number of primes
			if (numFacs % 2 == 0)
				count += (n-1)/factor;
			else
				count -= (n-1)/factor;
		} while(next_permutation(primeIndex.begin(), primeIndex.end()));
	

		// Vector starts with one 1, increasing until only one zero left
		primeIndex.erase(primeIndex.begin());
		primeIndex.push_back(1);
	}

	return (double)count / (n-1);
}


int main(int argc, char* argv[]) {
	const double goalRes = 15499.0 / 94744.0;
	
	for (int i = 9; i < 10; i++) {
		unsigned long long n = 1;
		for (int p = 0; p < i; p++)
			n *= primes[p];

		double r = res(n);
		printf("res(%14llu) = %.12f    goal = %.12f\n", n, r, goalRes);
		printf("diff = %.2e\n", r - goalRes);

		unsigned long long oldN = n;

		vector<int> mults;
		for (int x = 2; x < 19; x++)
			mults.push_back(x);

		for (auto m : mults) {
			n = oldN * m;
			r = res(n);		
			printf("\n");
			printf("multiplier = %d\n", m);	
			printf("res(%14llu) = %.9f    goal = %.9f\n", n, r, goalRes);			
			printf("diff = %.2e\n", r - goalRes);

			if (r < goalRes)
				break;
		}

		printf("\n\n");
		
		/**/
		
		if (r < goalRes) {			
			printf("N = %llu\n", n);
			break;
		}
	}
	
	fprintf(stdout, "done\n");

	getchar();

	return 0;
}

