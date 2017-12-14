// https://projecteuler.net/problem=101
// Optimum polynomial

#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long num_t;

int main(int argc, char* argv[]) {
	// d[k] is array of k-th differences
	vector<vector<num_t> > d;
	d.push_back(vector<num_t>());

	for (num_t n = 0; n <= 10; n++) {
		vector<num_t> pow(1, 1);
		for (int i = 1; i <= 10; i++)
			pow.push_back(pow.back() * (n+1));

		d[0].push_back(pow[0] - pow[1] + pow[2] - pow[3] + pow[4] - pow[5] + pow[6] - pow[7] + pow[8] - pow[9] + pow[10]);
	}

	// Create vector of all differences
	for (int i = 0; i < 10; i++) {
		d.push_back(vector<num_t>());
		for (int j = 1; j < d[i].size(); j++)
			d.back().push_back(d[i][j] - d[i][j-1]);
	}
	
	// Create vector of initial differences
	vector<num_t> diffs;
	diffs.push_back(0);
	for (int i = 1; i <= 10; i++)
		diffs.push_back(d[i][0]);

	num_t sum = 0;
	for (int k = 1; k <= 10; k++) {
		// Create polynomial where 1st to k-th differences are equal to the
		// original polynomial

		vector<num_t> dn = diffs;
		dn[0] = 1;
		for (int i = 0; i < k; i++)
			for (int j = 1; j < k; j++)
				dn[j-1] += dn[j];

		// Add first incorrect term
		sum += dn[0];
	}

	printf("sum = %llu\n", sum);

	getchar();

	return 0;
}
