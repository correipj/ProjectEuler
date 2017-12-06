// https://projecteuler.net/problem=59
// XOR decryption

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool isCharValid(unsigned char c) {
	if (c >= 'a' && c <= 'z')
		return true;

	if (c >= 'A' && c <= 'Z')
		return true;

	if (c >= '0' && c <= '9')
		return true;

	switch(c) {
	case ' ':
	case '.':
	case ',':
	case ':':
	case ';':
	case '(':
	case ')':
	case '!':
	case '\'':
		return true;
	default:
		return false;
	}
}

int main(int argc, char* argv[]) {
	ifstream fin("p059_cipher.txt");

	vector<unsigned int> chars;
	while(fin.good()) {		
		unsigned char comma;
		chars.push_back(0);
		fin >> chars.back() >> comma;
	}
	fin.close();

	vector<unsigned int> keys;

	bool foundFinal = false;
	string output;
		

	for (unsigned char k1 = 'a'; k1 <= 'z'; k1++) {
		if (foundFinal)	break;
		for (unsigned char k2 = 'a'; k2 <= 'z'; k2++) {
			if (foundFinal)	break;
			for (unsigned char k3 = 'a'; k3 <= 'z'; k3++) {
				if (foundFinal)	break;
				output.clear();

				bool corrupt = false;
				int i = 0;
				for (; i < 3*(chars.size()/3); i+=3) {
					unsigned char c1 = chars[i+0] ^ k1;
					unsigned char c2 = chars[i+1] ^ k2;
					unsigned char c3 = chars[i+2] ^ k3;

					if (isCharValid(c1) && isCharValid(c2) && isCharValid(c3)) {
						output.push_back(c1);
						output.push_back(c2);
						output.push_back(c3);
					} else {
						corrupt = true;
						break;
					}
				}

				if (corrupt)
					continue;

				// Add in last few characters that might not fit in key
				if (i+0 < chars.size())
					output.push_back(chars[i+0]^k1);
				if (i+1 < chars.size())
					output.push_back(chars[i+1]^k2);

				// Check for common words
				if (output.find("to ") == string::npos)
					continue;

				if (output.find("the ") == string::npos)
					continue;

				if (output.find(" and ") == string::npos)
					continue;

				foundFinal = true;
			}			
		}
	}

	printf("%s\n", output.c_str());

	unsigned int sum = 0;
	for (auto c : output)
		sum += c;

	printf("sum = %d\n", sum);

	getchar();

	return 0;
}

