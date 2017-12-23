// https://projecteuler.net/problem=147
// Rectangles in cross-hatched grids

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long num_t;

// 1 + 2 + ... + n
num_t sumN(const num_t& n) {
	return n*(n+1)/2;
}

num_t countRects(const num_t& a, const num_t& b) {
	if (a < b)
		return countRects(b, a);

	num_t sum = sumN(a) * sumN(b);

	if (a == 1 && b == 1)
		return 1;
	if (b == 1)
		return sum + a-1;
	
	vector<num_t> diag;

	for (int i = 1; i < b; i++)
		diag.push_back(2*i);
	for (int i = b; i < a; i++)
		diag.push_back(2*b-1);
	for (int i = b-1; i > 0; i--)
		diag.push_back(2*i);	

	while(!diag.empty() && diag.front()) {
		for (auto x : diag)
			sum += sumN(x);

		const auto it = max_element(diag.begin(), diag.end());
		const num_t val = *it;
		diag.erase(it);

		if (a != b)
			for (int i = 0; i < diag.size(); i++)
				if (diag[i] == val)
					diag[i]--;
	}

	return sum;
}

int main(int argc, char* argv[]) {
	num_t sum = 0;

	for (int a = 1; a <= 47; a++)
		for (int b = 1; b <= 43; b++)
			sum += countRects(a, b);

	printf("sum = %lld\n", sum);

	getchar();

	return 0;
}
