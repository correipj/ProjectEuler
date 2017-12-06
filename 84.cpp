// https://projecteuler.net/problem=84
// Monopoly odds

#include <iostream>
#include <vector>
#include <array>

using namespace std;

typedef array<double, 40> odds_t;

bool isCC(unsigned int n) {
	return n == 02 || n == 17 || n == 33;
}

bool isCH(unsigned int n) {
	return n == 07 || n == 22 || n == 36;
}

unsigned int nextR(unsigned int n) {
	if (n > 35 || n < 05)
		return 05;

	if (n > 05 && n < 15)
		return 15;

	if (n > 15 && n < 25)
		return 25;

	if (n > 25 && n < 35)
		return 35;

	return -1;	// o shit wat r u doin
}

unsigned int nextU(unsigned int n) {
	if (n < 12 || n > 28)
		return 12;

	if (n > 12 && n < 28)
		return 28;

	return -1;	// o shit wat r u doin
}

odds_t calcTurnEndpoints(unsigned int start, const unsigned int turnN) {
	odds_t ret;
	for (auto& r : ret)
		r = 0;

	/*
	// 6-Sided
	array<double, 13> diceRoll;
	diceRoll[ 0] = 0.0;		// Can't roll 0
	diceRoll[ 1] = 0.0;		// Can't roll 1
	diceRoll[ 2] = 1.0/36.0;
	diceRoll[ 3] = 2.0/36.0;
	diceRoll[ 4] = 3.0/36.0;
	diceRoll[ 5] = 4.0/36.0;
	diceRoll[ 6] = 5.0/36.0;
	diceRoll[ 7] = 6.0/36.0;
	diceRoll[ 8] = 5.0/36.0;
	diceRoll[ 9] = 4.0/36.0;
	diceRoll[10] = 3.0/36.0;
	diceRoll[11] = 2.0/36.0;
	diceRoll[12] = 1.0/36.0;
	*/

	
	// 4-Sided
	array<double, 9> diceRoll;
	diceRoll[0] = 0.0;		// Can't roll 0
	diceRoll[1] = 0.0;		// Can't roll 1
	diceRoll[2] = 1.0/16.0;
	diceRoll[3] = 2.0/16.0;
	diceRoll[4] = 3.0/16.0;
	diceRoll[5] = 4.0/16.0;
	diceRoll[6] = 3.0/16.0;
	diceRoll[7] = 2.0/16.0;
	diceRoll[8] = 1.0/16.0;
	
	// three doubles in a row -> go to jail
	if (turnN >= 3) {
		const double diceChance = 1.0/6.0;
		const double jailChance = diceChance*diceChance*diceChance;
		ret[10] += jailChance;
		for (auto& d : diceRoll)
			d *= (1.0 - jailChance);
	}

	for (int i = 0; i < diceRoll.size(); i++) {
		unsigned int n = (start+i) % 40;

		if (isCC(n)) {
			// Advance to GO
			ret[0] += diceRoll[i] * (1.0/16.0);
			// Go to Jail
			ret[10] += diceRoll[i] * (1.0/16.0);
			// No movement
			ret[n] += diceRoll[i] * (14.0/16.0);
		} else if (isCH(n)) {
			// Advance to GO
			ret[0] += diceRoll[i] * (1.0/16.0);
			// Go to JAIL
			ret[10] += diceRoll[i] * (1.0/16.0);
			// Go to C1
			ret[11] += diceRoll[i] * (1.0/16.0);
			// Go to E3
			ret[24] += diceRoll[i] * (1.0/16.0);
			// Go to H2
			ret[39] += diceRoll[i] * (1.0/16.0);
			// Go to R1
			ret[05] += diceRoll[i] * (1.0/16.0);
			// Go to next R (railway company)			
			ret[nextR(n)] += diceRoll[i] * (1.0/16.0);		// ?
			// Go to next R
			ret[nextR(n)] += diceRoll[i] * (1.0/16.0);		// ?
			// Go to next U (utility company)
			ret[nextU(n)] += diceRoll[i] * (1.0/16.0);
			// Go back 3 squares.
			if (n-3 == 30)
				ret[10] += diceRoll[i] * (1.0/16.0);
			else if (isCC(n-3)) {
				// Our chance card brough us to community chest!
				// Advance to GO
				ret[0] += diceRoll[i] * (1.0/16.0) * (1.0/16.0);
				// Go to Jail
				ret[10] += diceRoll[i] * (1.0/16.0) * (1.0/16.0);
				// No movement
				ret[n-3] += diceRoll[i] * (14.0/16.0) * (1.0/16.0);
			} else
				ret[(n-3)%40] += diceRoll[i] * (1.0/16.0);
			// No movement
			ret[n] += diceRoll[i] * (6.0/16.0);
		} else if (n == 30) {
			// Go to JAIL
			ret[10] += diceRoll[i];
		} else {
			ret[n] += diceRoll[i];
		}
	}

	return ret;
}

double calcError(const odds_t& a, const odds_t& b) {
	double ret = 0;

	for (int i = 0; i < 40; i++)
		ret += fabs(a[i] - b[i]);

	return ret;
}

bool compByOdds(const pair <int, double>& a, const pair <int, double>& b) {
	return a.second < b.second;
}

int main(int argc, char* argv[]) {
	vector<odds_t> oddsAfterTurn;
	// After 0 turns, 100% chance of being on square 00, 0% chance for others
	oddsAfterTurn.push_back(odds_t());
	for (auto& n : oddsAfterTurn[0])
		n = 0;
	oddsAfterTurn[0][0] = 1.0;

	for (int turn = 1; turn < 1000; turn++) {
		oddsAfterTurn.push_back(odds_t());
		for (auto& n : oddsAfterTurn[turn])
			n = 0;

		const odds_t lastTurn = oddsAfterTurn[turn-1];
		for (int start = 0; start < 40; start++) {
			const odds_t endpts = calcTurnEndpoints(start, turn);

			for (int i = 0; i < 40; i++)
				oddsAfterTurn[turn][i] += lastTurn[start] * endpts[i];
		}

		// Calc change between this turn and previous turn
		const double error = calcError(oddsAfterTurn[turn], oddsAfterTurn[turn-1]);

		if (error < 0.00001)
			break;
	}

	printf("%d iters\n", oddsAfterTurn.size());

	vector<pair <int, double> > place;
	for(int i = 0; i < 40; i++)
		place.push_back(make_pair(i, oddsAfterTurn.back()[i]));

	sort(place.rbegin(), place.rend(), compByOdds);

	printf("\n");
	printf("Top 3 places:\n");
	printf("%02d    %5.2f\n", place[0].first, 100*place[0].second);
	printf("%02d    %5.2f\n", place[1].first, 100*place[1].second);
	printf("%02d    %5.2f\n", place[2].first, 100*place[2].second);
	printf("\n");
	printf("%02d",   place[0].first);
	printf("%02d",   place[1].first);
	printf("%02d\n", place[2].first);


	getchar();

	return 0;
}

