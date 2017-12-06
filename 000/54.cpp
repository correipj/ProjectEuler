// https://projecteuler.net/problem=54

#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <utility>
#include <vector>

using namespace std;

typedef array<string, 5> hand_t;

void printHands(const hand_t& h1, const hand_t& h2) {
	printf("h1 = ");
	for (auto s : h1)
		printf("%s ", s.c_str());
	printf("\n");
	
	printf("h2 = ");
	for (auto s : h2)
		printf("%s ", s.c_str());
	printf("\n");
}

unsigned int val(unsigned char c) {
	switch(c) {
	case '1':	return 1;	// Special case for a low ace
	case '2':	return 2;
	case '3':	return 3;
	case '4':	return 4;
	case '5':	return 5;
	case '6':	return 6;
	case '7':	return 7;
	case '8':	return 8;
	case '9':	return 9;
	case 'T':	return 10;
	case 'J':	return 11;
	case 'Q':	return 12;
	case 'K':	return 13;
	case 'A':	return 14;
	}

	return 0;
}

bool compCards(const string& c1, const string& c2) {
	return val(c1[0]) < val (c2[0]);
}

bool compHands(const hand_t& c1, const hand_t& c2) {	
	return lexicographical_compare(c1.begin(), c1.end(), c2.begin(), c2.end(), compCards);
}

bool isFlush(const hand_t& h) {
	unsigned char suit = h.front()[1];

	for (int i = 1; i < h.size(); i++)
		if (h[i][1] != suit)
			return false;

	return true;
}

bool isStraight(const hand_t& h, bool alt = false) {
	if (alt == false) {
		bool hasAce = false;
		hand_t altH(h);
		for (int i = 0; i < h.size(); i++) {
			if (h[i][0] == 'A') {
				altH[i][0] = '1';
				hasAce = true;
			}
		}

		if (hasAce) {
			sort(altH.rbegin(), altH.rend());

			if (isStraight(altH, true)) {
				printf("oooh\n");
				return true;
			}
		}
		
	}

	unsigned char high = h.front()[0];

	for (int i = 1; i < h.size(); i++)
		if (h[i][0] != high-i)
			return false;

	return true;
}

bool isSF(const hand_t& h) {
	return isStraight(h) && isFlush(h);
}

bool isRF(const hand_t& h) {
	return isSF(h) && h.front()[0] == 'A';
}

bool is4OAK(const hand_t& h) {
	array<unsigned int, 5> count;
	for (auto& c : count)
		c = 0;

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (h[i][0] == h[j][0])
				count[i]++;

	auto it = max_element(count.begin(), count.end());

	if (*it == 4)
		return true;

	return 0;
}

bool isFH(const hand_t& h) {
	vector<unsigned int> count(5,0);

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (h[i][0] == h[j][0])
				count[i]++;
			
	// Check for pair
	if (find(count.begin(), count.end(), 2) == count.end())
		return false;

	// Check for 3 of a kind
	if (find(count.begin(), count.end(), 3) == count.end())
		return false;

	return true;
}

bool is3OAK(const hand_t& h) {
	array<unsigned int, 5> count;
	for (auto& c : count)
		c = 0;

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (h[i][0] == h[j][0])
				count[i]++;

	auto it = max_element(count.begin(), count.end());

	if (*it == 3)
		return true;

	return false;
}

bool is2P(const hand_t& h) {
	// Assume no higher hands exist like 3 of a kind

	// Find first pair
	bool foundPair = false;
	int n1, n2;
	for (int i = 0; i < 5; i++)
		for (int j = i+1; j < 5; j++)
			if (h[i][0] == h[j][0]) {
				n1 = i;
				n2 = j;
				foundPair = true;
				break;
			}

	if (!foundPair)
		return false;

	// Find second pair
	for (int i = 0; i < 5; i++) {
		if (i == n1 || i == n2)
			continue;

		for (int j = i+1; j < 5; j++) {
			if (j == n1 || j == n2)
				continue;

			if (h[i][0] == h[j][0])
				return true;
		}
	}

	return false;
}

bool is1P(const hand_t& h) {
	// Assume no higher hands exist like 2 pair
	for (int i = 0; i < 5; i++)
		for (int j = i+1; j < 5; j++)
			if (h[i][0] == h[j][0])
				return true;

	return false;
}

bool specCase(const hand_t& h1, const hand_t& h2) {
	// Both h1 and h2 have a single pair each
	unsigned int p1=0;
	unsigned int p2=0;
	
	for (int i = 0; i < h1.size() && p1 == 0; i++)
		for (int j = i+1; j < h1.size() && p1 == 0; j++)
			if(h1[i][0] == h1[j][0])
				p1 = val(h1[i][0]);

	for (int i = 0; i < h2.size() && p2 == 0; i++)
		for (int j = i+1; j < h2.size() && p2 == 0; j++)
			if(h2[i][0] == h2[j][0])
				p2 = val(h2[i][0]);

	if (p1 == p2)
		return compHands(h2, h1);

	return p1 > p2;
}

bool p1Winner(const hand_t& h1, const hand_t& h2) {
	unsigned int b1, b2;
	
	// Royal flush
	b1 = isRF(h1);
	b2 = isRF(h2);

	// both royal flushes? wtf
	if(b1 && b2) {
		printf("fixme\n");
		return compHands(h2, h1);
	} else if (b1)
		return true;
	else if (b2)
		return false;

	// Straight flush
	b1 = isSF(h1);
	b2 = isSF(h2);

	if(b1 && b2) {
		printf("fixme\n");
		return compHands(h2, h1);
	} else if (b1)
		return true;
	else if (b2)
		return false;

	// Four of a kind
	b1 = is4OAK(h1);
	b2 = is4OAK(h2);
	
	if(b1 && b2) {
		printf("fixme\n");
		return compHands(h2, h1);
	} else if (b1)
		return true;
	else if (b2)
		return false;

	// Full House
	b1 = isFH(h1);
	b2 = isFH(h2);

	if(b1 && b2) {
		printf("fixme\n");
		return compHands(h2, h1);
	} else if (b1)
		return true;
	else if (b2)
		return false;

	// Flush
	b1 = isFlush(h1);
	b2 = isFlush(h2);

	if(b1 && b2) {
		printf("fixme\n");
		return compHands(h2, h1);
	} else if (b1)
		return true;
	else if (b2)
		return false;

	// Straight
	b1 = isStraight(h1);
	b2 = isStraight(h2);

	if(b1 && b2) {
		printf("fixme\n");
		return compHands(h2, h1);
	} else if (b1)
		return true;
	else if (b2)
		return false;

	// 3OAK
	b1 = is3OAK(h1);
	b2 = is3OAK(h2);

	if(b1 && b2) {
		printf("fixme\n");
		return compHands(h2, h1);
	} else if (b1)
		return true;
	else if (b2)
		return false;

	// Two Pairs
	b1 = is2P(h1);
	b2 = is2P(h2);

	if(b1 && b2) {
		printf("fixme\n");
		return compHands(h2, h1);
	} else if (b1)
		return true;
	else if (b2)
		return false;

	// One Pair
	b1 = is1P(h1);
	b2 = is1P(h2);

	if(b1 && b2)
		return specCase(h1, h2);
	else if (b1)
		return true;
	else if (b2)
		return false;

	// High card

	return compHands(h2, h1);
}

int main(int argc, char* argv[]) {
	ifstream fin("poker.txt");
	
	vector<pair<hand_t, hand_t> > hands;

	printf("loading...");
	while(fin.good()) {
		hand_t p1, p2;
		
		for (auto& s : p1) {
			s.resize(2);
			fin >> s[0];
			fin >> s[1];
		}
		sort(p1.rbegin(), p1.rend(), compCards);

		for (auto& s : p2) {
			s.resize(2);
			fin >> s[0];
			fin >> s[1];
		}
		sort(p2.rbegin(), p2.rend(), compCards);

		if (p1.front()[0] == 0)
			break;

		hands.push_back(make_pair(p1, p2));
	}
	fin.close();
	printf("done\n");

	unsigned int count = 0;
	for (auto hand : hands)
		if (p1Winner(hand.first, hand.second))
			count++;

	printf("count = %d\n", count);

	getchar();

	return 0;
}