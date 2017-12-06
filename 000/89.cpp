// https://projecteuler.net/problem=89
// Roman numerals

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int rom2Num (string s) {
	// Add a blank char to the end so we don't worry about overflow
	s.push_back(' ');

	int n = 0;

	for (int i = 0; i < s.size(); i++) {
		switch(s[i]) {
		case 'M':
			n += 1000;	break;
		case 'D':
			n += 500;	break;
		case 'C':
			if (s[i+1] == 'M') {
				n += 900;
				i++;
			} else if (s[i+1] == 'D') {
				n += 400;
				i++;
			} else
				n += 100;
			break;
		case 'L':
			n += 50;	break;
		case 'X':
			if (s[i+1] == 'C') {
				n += 90;
				i++;
			} else if (s[i+1] == 'L') {
				n += 40;
				i++;
			} else
				n += 10;
			break;
		case 'V':
			n += 5;		break;
		case 'I':
			if (s[i+1] == 'X') {
				n += 9;
				i++;
			} else if (s[i+1] == 'V') {
				n += 4;
				i++;
			} else
				n += 1;			
			break;
		}
	}

	return n;
}

string num2Rom (int n) {
	string s;

	while (n) {
		if (n >= 1000) {
			s += 'M';
			n -= 1000;
			continue;
		}
		if (n >= 900) {
			s += 'C';
			s += 'M';
			n -= 900;
		}
		if (n >= 500) {
			s += 'D';
			n -= 500;
			continue;
		}
		if (n >= 400) {
			s += 'C';
			s += 'D';
			n -= 400;
			continue;
		}
		if (n >= 100) {
			s += 'C';
			n -= 100;
			continue;
		}
		if (n >= 90) {
			s += 'X';
			s += 'C';
			n -= 90;
			continue;
		}
		if (n >= 50) {
			s += 'L';
			n -= 50;
			continue;
		}
		if (n >= 40) {
			s += 'X';
			s += 'L';
			n -= 40;
			continue;
		}
		if (n >= 10) {
			s += 'X';
			n -= 10;
			continue;
		}
		if (n >= 9) {
			s += 'I';
			s += 'X';
			n -= 9;
			continue;
		}
		if (n >= 5) {
			s += 'V';
			n -= 5;
			continue;
		}
		if (n >= 4) {
			s += 'I';
			s += 'V';
			n -= 4;
			continue;
		}
		if (n >= 1) {
			s += 'I';
			n -= 1;
			continue;
		}
	}

	return s;
}

int main(int argc, char* argv[]) {
	ifstream fin("p089_roman.txt");

	int nSaved = 0;
	string line;
	while(!fin.eof()) {
		getline(fin, line);

		nSaved += line.length() - num2Rom(rom2Num(line)).length();
	}

	fin.close();

	printf("%d chars saved\n", nSaved);

	getchar();

	return 0;
}

