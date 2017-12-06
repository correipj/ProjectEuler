// https://projecteuler.net/problem=44
// Pentagon numbers

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


int main(int argc, char* argv[]) {
	vector<unsigned long> penta;
	penta.push_back(1);
	for (int i = 2; i < 2500; i++)
		penta.push_back(penta.back() + 3*i - 2);
		
	const unsigned int maxD = penta.size()-3;
	for (int d = 1; d <= maxD; d++) {
		for (int i = 0; i < penta.size() - d; i++) {
			// Check if sum is pentagonal
			if (!binary_search(penta.begin(), penta.end(), penta[i] + penta[i+d]))
				continue;
			
			// Check if difference is pentagonal
			if (!binary_search(penta.begin(), penta.end(), penta[i+d] - penta[i]))
				continue;

			printf("found pair %lu and %lu\n", penta[i], penta[i+d]);
			printf("sum = %lu, ", penta[i] + penta[i+d]);
			printf("difference = %lu\n", penta[i+d] - penta[i]);
			getchar();
		}
	}

	printf("done\n");

	getchar();

	return 0;
}

