// https://projecteuler.net/problem=109
// Darts

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

struct dart_t {
	int val;
	int mult;

	dart_t(int v, int m = 1) {
		val = v;
		mult = m;
	}

	int score() const {
		return val * mult;
	}
};

int main(int argc, char* argv[]) {
	const unsigned int lim = 100;
	
	vector<dart_t> shots1;
	vector<pair<dart_t, dart_t> > shots2;

	// First dart combinations
	for (int n1 = 1; n1 <= 21; n1++)
		for (int m1 = 1; m1 <= 3; m1++) {
			dart_t d1(n1, m1);

			// Consider special shots			
			if (n1 == 21 && m1 == 3) {
				// Dont consider missed shots
				continue;
			} else if (n1 == 21) {
				// Bullseye can only be single/double
				d1.mult = m1;
				d1.val = 25;
			}

			if (d1.score() >= lim)
				continue;

			shots1.push_back(d1);

			// Second dart combinations
			for (int n2 = n1; n2 <= 21; n2++)
				for (int m2 = 1; m2 <= 3; m2++) {
					if (n1 == n2 && m2 < m1)
						continue;

					dart_t d2(n2, m2);

					// Consider special shots			
					if (n2 == 21 && m2 == 3) {
						// Dont consider missed shots
						continue;
					} else if (n2 == 21) {
						// Bullseye can only be single/double
						d2.mult = m2;
						d2.val = 25;
					}

					if (d1.score() + d2.score() >= lim)
						continue;

					shots2.push_back(make_pair(d1, d2));
				}
		}

	unsigned int count = 0;
	for (dart_t d3(1, 2); d3.val <= 21; d3.val++) {
		if (d3.val == 21)
			d3.val = 25;

		if (d3.score() < lim)
			count++;

		for (auto d2 : shots1)
			if (d2.score() + d3.score() < lim)
				count++;

		for (auto p : shots2)
			if (p.first.score() + p.second.score() + d3.score() < lim)
				count++;
	}

	printf("count = %lu\n", count);
	
	getchar();

	return 0;
}
