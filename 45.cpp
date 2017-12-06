// https://projecteuler.net/problem=45

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
	vector<unsigned long long> triangle;
	vector<unsigned long long> pentagon;
	vector<unsigned long long> hexagon;
	
	triangle.push_back(1);
	pentagon.push_back(1);
	hexagon.push_back(1);

	for (int i = 2; i < 100000; i++) {
		triangle.push_back(triangle.back() + i);
		pentagon.push_back(pentagon.back() + 3*i-2);
		hexagon.push_back(hexagon.back() + 4*i-3);
	}

	unsigned n = 0;
	for (int i = 285; i < triangle.size(); i++) {
		auto t = triangle[i];

		if (binary_search(pentagon.begin(), pentagon.end(), t) == false)
			continue;
		
		if (binary_search(hexagon.begin(), hexagon.end(), t) == false)
			continue;
		
		printf("%d  is triangle, pentagon and hexagon\n", t);

		getchar();
	}
	
	getchar();

	return 0;
}

