// https://projecteuler.net/problem=74
// Digit factorial chains

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

unsigned int fact(unsigned int n) {
	switch(n) {
	case 0:
	case 1:	return 1;
	case 2:	return 2;
	case 3:	return 6;
	case 4:	return 24;
	case 5:	return 120;
	case 6:	return 720;
	case 7:	return 5040;
	case 8:	return 40320;
	case 9:	return 362880;
	}
}

string equivStr(unsigned long n) {
	string s(to_string(n));
	sort(s.begin(), s.end());

	return s;
}

unsigned int sumDigitFact(unsigned int n) {
	unsigned int sum = 0;

	while(n) {
		sum += fact(n % 10);
		n /= 10;
	}

	return sum;
}

int main(int argc, char* argv[]) {	
	const unsigned int N = 1000000;

	//    3 == 16
	// 1479 == 60

	vector<unsigned int> nonRep(3*N, 0);
	
	// Pre-set values for cyclic and fixed numbers. Saves us from detecting
	// cycles as numbers are computed
	nonRep[   169] = 3;
	nonRep[363601] = 3;
	nonRep[  1454] = 3;

	nonRep[  871] = 2;
	nonRep[45361] = 2;

	nonRep[  872] = 2;
	nonRep[45362] = 2;
	
	nonRep[1] = 1;
	nonRep[2] = 1;
	nonRep[145] = 1;
	nonRep[40585] = 1;

	unsigned int count = 0;
	
	for (int start = 1; start < N; start++) {
		vector<unsigned int> prev;
		prev.push_back(start);

		while(nonRep[prev.back()] == 0)
			prev.push_back(sumDigitFact(prev.back()));

		for (int i = prev.size()-2; i >= 0; i--)
			nonRep[prev[i]] = nonRep[prev[i+1]] + 1;

		if (nonRep[prev.front()] == 60)
			count++;
	}

	printf("count = %d\n", count);

	getchar();
	
	return 0;
}

