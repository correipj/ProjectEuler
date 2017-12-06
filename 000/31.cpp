// https://projecteuler.net/problem=31
// Coin sums

#include <iostream>
#include <array>

using namespace std;

array<int, 8> coins = {1, 2, 5, 10, 20, 50, 100, 200};

int nPerms (int total, int maxCoin = 200) {
	if (total == 0 || maxCoin == 1)
		return 1;
	
	int sum = 0;
	for(int coin : coins) {
		if (coin > total || coin > maxCoin)
			break;

		sum += nPerms(total-coin, coin);
	}

	return sum;
}

int main(int argc, char* argv[]) {	
	printf("%d\n", nPerms(200, 200));

	getchar();

	return 0;
}
