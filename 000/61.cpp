// https://projecteuler.net/problem=61

#include <iostream>
#include <vector>
#include <array>
#include <map>

using namespace std;

// If n == __46, look for numbers in v of of the form 46__. There are about four
// cases across all six lists with more than one solution. Just ignore these for
// now and if we don't find a solution then we know where to look :)
bool findCycledInVec(const vector<unsigned int>& v, const unsigned int& n, unsigned int* r1) {
	const unsigned int a = n % 100;

	for (auto i : v)
		if (i >= 100*a && i < 100*(a+1)) {
			*r1 = i;
			return true;
		}
	
	return false;
}

int main(int argc, char* argv[]) {
	map<unsigned char, vector<unsigned int> > polyNums;

	// Create lists of triangle numbers, square numbers, ... etc
	for(int i = 3; i <= 8; i++) {
		polyNums[i] = vector<unsigned int>();

		unsigned int sum = 0;
		int n = 0;
		while(sum < 10000) {
			if (sum >= 1000)
				polyNums[i].push_back(sum);
						
			sum += (i-2)*(++n) - (i-3);
		}
	}

	// array sorting the order in which we will cycle through each list
	vector<int> combo = {4, 5, 6, 7, 8};
	bool found = false;

	// Check each combination of permutation array
	do {	
		// for each starting number, find corresponding cycled number
		for (int i = 0; i < polyNums[3].size(); i++) {
			array<unsigned int, 6> n;
			n.front() = polyNums[3][i];

			bool brokenCycle = false;
			for (int j = 0; j < 5; j++)
				if (!findCycledInVec(polyNums[combo[j]], n[j], &n[j+1])) {
					brokenCycle = true;
					break;
				}

			// If our last number doesnt have a match in next list, go to next number
			if (brokenCycle)
				continue;

			// Check if front and back of cycle match up
			if (n.front() / 100 == n.back() % 100) {	
				unsigned long sum = 0;
				for (auto a : n)
					sum += a;

				printf("sum = %lu\n", sum);
				found = true;
			}
		}
	} while(!found && next_permutation(combo.begin(), combo.end()));
	
	getchar();

	return 0;
}

