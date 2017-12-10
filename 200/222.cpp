// https://projecteuler.net/problem=222
// Sphere Packing

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const double Rpipe = 50.0;

// Solved with the power of noticing patterns in smaller cases.
// There are 21! different orders in which to stack the 21 balls, far too many
// to test all of them. Test 6! ways to stack 6 balls, find pattern, apply to
// case of 21 balls. ezpz

int main(int argc, char* argv[]) {
	vector<double> R;
	for (double i = 30.0; i <= 50.0; i += 1.0)
		R.push_back(i);

	vector<vector<double> > zDiff;
	for (int i = 0; i < R.size(); i++)
		zDiff.push_back(vector<double>(R.size()));
	
	for (int i = 0; i < R.size(); i++)
		for (int j = i+1; j < R.size(); j++) {
			const double d = R[i] + R[j];
			const double dx = 2*Rpipe - d;
			const double diff = sqrt(d*d - dx*dx);

			zDiff[i][j] = diff;
			zDiff[j][i] = diff;
		}

	vector<int> order;
	for (int i = 0; i < R.size(); i++)
		order.push_back(i);
	
	/*vector<int> minOrder;
	double minSum = 99999999999999.0;

	int a = -1;

	do {
		for (auto o : order)
			printf("%.0f ", R[o]);
		printf("   ");

		// Test order
		double sum = R[order.front()] + R[order.back()];

		for (int i = 0; i < order.size()-1; i++)
			sum += zDiff[order[i]][order[i+1]];

		printf("sum = %.3f min = %.3f   ", sum, minSum);

		if (sum < minSum) {
			minSum = sum;
			minOrder = order;
			printf("---");
		}

		printf("\n");
	} while(next_permutation(order.begin(), order.end()));
	printf("\n\n");

	printf("minimum sum = %.3f\n", minSum);
	printf("minimum order:\n");
	for (auto o : minOrder)
		printf("%.0f ", R[o]);
	printf("\n");
	/**/

	//	order = {19, 17, 15, 13, 11, 9, 7, 5, 3, 1, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
	printf("constructed order:\n");
	for (int i = 0; i < order.size(); i++)
		if (i % 2 == 1) {
			// Move odd indicies to beginning
			order.erase(order.begin()+i);
			order.insert(order.begin(), i);
		}

	// Test constructed order
	double sum = R[order.front()] + R[order.back()];

	for (int i = 0; i < order.size()-1; i++)
		sum += zDiff[order[i]][order[i+1]];
	printf("length = %.0f um\n", 1000*sum);

	getchar();

	return 0;
}
