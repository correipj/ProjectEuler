// https://projecteuler.net/problem=62
// Cubic permutations

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
	unsigned long long N = 9000;
	map<string, set<unsigned long long> > m;


	for (unsigned long long i = 1; i <= N; i++) {
		string s(to_string(i*i*i));
		sort(s.begin(), s.end());
		m[s].insert(i);

		if (m[s].size() == 5) {
			printf("%llu\n", *m[s].begin());
			break;
		}		
	}

	getchar();
	
	return 0;
}

