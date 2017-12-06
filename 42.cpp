// https://projecteuler.net/problem=42

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

unsigned int wordVal(const string& s) {
	unsigned int sum = 0;
	for (auto c : s) {
		sum += c - 'A' + 1;
	}
	return sum;
}

int main(int argc, char* argv[]) {
	ifstream fin("words.txt");

	vector<unsigned int> tri;
	tri.push_back(1);
	for (int i = 2; i < 50; i++)
		tri.push_back(tri.back() + i);

	unsigned int count = 0;

	while(fin.good()) {
		unsigned char c;
		// read init quote char
		fin >> c;

		string s;
		while(1) {
			fin >> c;

			if (c == '\"')
				break;

			s += c;
		}

		unsigned int val = wordVal(s);
		if (binary_search(tri.begin(), tri.end(), val))
			count++;
		
		// read comma char
		fin >> c;
	}
	fin.close();

	printf("count = %d\n", count);

	getchar();

	return 0;
}

