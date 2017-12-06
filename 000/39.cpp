// https://projecteuler.net/problem=39
// Integer right triangles

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct pyth {
	int a, b, c;
};

int main(int argc, char* argv[]) {
	queue<pyth> Q;
	Q.push({3, 4, 5});

	int a, b, c;

	const unsigned int N = 1000;

	vector<int> perimCount(N+1, 0);

	while(!Q.empty()) {
		pyth p = Q.front();
		Q.pop();
				
		int sum = p.a + p.b + p.c;
		if (sum > N)
			continue;
		
		for (int i = sum; i < perimCount.size(); i += sum)
			perimCount[i]++;

		a = 1*p.a - 2*p.b + 2*p.c;
		b = 2*p.a - 1*p.b + 2*p.c;
		c = 2*p.a - 2*p.b + 3*p.c; 
		Q.push({a, b, c});
		
		a = 1*p.a + 2*p.b + 2*p.c;
		b = 2*p.a + 1*p.b + 2*p.c;
		c = 2*p.a + 2*p.b + 3*p.c; 
		Q.push({a, b, c});
		
		a = -1*p.a + 2*p.b + 2*p.c;
		b = -2*p.a + 1*p.b + 2*p.c;
		c = -2*p.a + 2*p.b + 3*p.c; 
		Q.push({a, b, c});
	}

	auto it = max_element(perimCount.begin(), perimCount.end());
	printf("max = %lu\n", distance(perimCount.begin(), it));

	getchar();

	return 0;
}
