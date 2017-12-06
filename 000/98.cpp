// https://projecteuler.net/problem=98
// Anagramic squares

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef map<unsigned char, unsigned int> charMap_t;

// Compares words based on length
// if equal length, compare lexicographically
bool lenComp(const string& a, const string& b) {
	if (a.length() == b.length())
		return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());

	return a.length() < b.length();
}

unsigned int nDigits(unsigned long n) {
	return 1+floor(log10((double)n));
}

// d=0 is most significant digit
unsigned int getDigit(unsigned long n, unsigned int d) {
	const unsigned int nd = nDigits(n);
	
	if (d >= nDigits(n))
		return 0;

	unsigned int c = nDigits(n) - d;

	while(--c)
		n /= 10;

	return n%10;
}

// Squares with duplicate digits won't work
bool isValidSquare(unsigned long n) {
	const unsigned int nd = nDigits(n);

	for (int i = 0; i < nd; i++) {
		const unsigned int currD = getDigit(n, i);

		for (int j = i+1; j < nd; j++)
			if (getDigit(n, j) == currD)
				return false;
	}

	return true;
}

bool isAnagram(const string& a, const string& b) {
	if (a.size() != b.size())
		return false;

	string s1(a);
	string s2(b);
	
	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());

	return s1 == s2;
}

unsigned long applyMap(const charMap_t& m, const string& s) {
	unsigned long sum = 0;

	for (unsigned char c : s)
		sum = 10*sum + m.at(c);

	return sum;
}

int main(int argc, char* argv[]) {
	vector<string> words;
	ifstream fin("p098_words.txt");

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

		words.push_back(s);

		// read comma char
		fin >> c;
	}
	
	fin.close();

	// Order words by their length
	sort(words.begin(), words.end(), lenComp);

	// Make list of perfect squares of up to 9 digits
	// squares[4] contains 4 digit perfect squares
	vector<vector<unsigned long> > squares(10);
	for (unsigned long i = 1; i < 1000000; i++) {
		unsigned long sq = i * i;

		if (nDigits(sq) >= squares.size())
			break;

		squares[nDigits(sq)].push_back(sq);
	}

	// Make a subset of these squares containing only perfect squares without
	// repeating digits
	vector<vector<unsigned long> > validSquares(squares.size());
	for (int i = 0; i < squares.size(); i++)
		for (auto sq : squares[i])
			if (isValidSquare(sq))
				validSquares[i].push_back(sq);


	unsigned long maxSq = 0;

	for (int wordN = 0; wordN < words.size(); wordN++) {
		const string word = words[wordN];

		// Create list of anagrams
		vector<string> anagrams;
		for (int i = wordN+1; i < words.size(); i++) {
			if (words[i].size() > word.size())
				break;

			if (isAnagram(words[i], word))
				anagrams.push_back(words[i]);
		}

		// Don't test words without anagrams
		if (anagrams.empty())
			continue;
		
		// Create a string of characters from word with all duplicates removed
		// MANAGEMENT -> MAN_GE___T -> MANGET
		string chars = word;
		for (int i = 0; i < chars.size(); i++)
			for (int j = i+1; j < chars.size(); j++)
				if (chars[j] == chars[i])
					chars.erase(chars.begin() + j--);
				
		// Get list of squares with # of digits equal to # of unique chars
		// sqs are "valid" squares, no repeating digits
		// allSqs are all squares
		const vector<unsigned long> sqs = validSquares[chars.length()];
		const vector<unsigned long> allSqs = squares[chars.length()];

		// Test each square
		for (auto n : sqs) {
			// Create a map from unique characters in word to digits in square
			charMap_t m;
			for (int i = 0; i < chars.size(); i++)
				m[chars[i]] = getDigit(n, i);
			
			// Test mapping against anagrams
			for (auto ana : anagrams) {
				// leading 0s not allowed
				if (m[ana.front()] == 0)
					continue;

				// Get number formed by anagram
				const unsigned long mappedN = applyMap(m, ana);

				// Don't bother checking numbers that won't break maximum
				if (mappedN < maxSq && n < maxSq)
					continue;

				// Check if its a perfect square
				if (binary_search(allSqs.begin(), allSqs.end(), mappedN))
					maxSq = max(maxSq, max(mappedN, n));
			}
		}
	}

	printf("max = %lu\n", maxSq);

	
	getchar();

	return 0;
}
