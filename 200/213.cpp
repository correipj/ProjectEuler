// https://projecteuler.net/problem=213
// Flea Circus

#include <iostream>
#include <vector>

using namespace std;

const unsigned int SIZE = 30;

typedef vector<vector<double> > grid_t;

void printGrid(const grid_t& g) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			printf("%6.3f ", g[i][j]);
		printf("\n");
	}
}

double numAdjacent(unsigned int x, unsigned int y) {
	double ret = 4.0;

	if (x == 0 || x == SIZE-1)
		ret -= 1.0;
	if (y == 0 || y == SIZE-1)
		ret -= 1.0;

	return ret;
}

grid_t fleaProb(unsigned int x, unsigned int y) {
	grid_t g;
	for (int i = 0; i < SIZE; i++)
		g.push_back(vector<double>(SIZE, 0));

	g[y][x] = 1.0;

	const int dx[4] = {-1, 0, 0, 1};
	const int dy[4] = {0, -1, 1, 0};

	for (int iter = 1; iter <= 50; iter++) {
		grid_t newG;
		for (int i = 0; i < SIZE; i++)
			newG.push_back(vector<double>(SIZE, 0));

		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				for (int d = 0; d < 4; d++) {
					const int x = j + dx[d];
					const int y = i + dy[d];

					if (x < 0 || x > SIZE-1)
						continue;
					if (y < 0 || y > SIZE-1)
						continue;

					newG[y][x] += g[i][j] / numAdjacent(i, j);
				}


		g = newG;
	}

	return g;
}

int main(int argc, char* argv[]) {
	grid_t grid;
	for (int i = 0; i < SIZE; i++)
		grid.push_back(vector<double>(SIZE, 1.0));
	
	for (int i = 0; i < SIZE/2; i++)
		for (int j = i; j < SIZE/2; j++) {
			grid_t g = fleaProb(i, j);

			for (int y = 0; y < SIZE; y++)
				for (int x = 0; x < SIZE; x++) {
					grid[y][x] *= 1.0 - g[y][x];
					grid[y][x] *= 1.0 - g[SIZE-1-y][x];
					grid[y][x] *= 1.0 - g[y][SIZE-1-x];
					grid[y][x] *= 1.0 - g[SIZE-1-y][SIZE-1-x];

					if (i != j) {
						grid[x][y] *= 1.0 - g[y][x];
						grid[x][y] *= 1.0 - g[SIZE-1-y][x];
						grid[x][y] *= 1.0 - g[y][SIZE-1-x];
						grid[x][y] *= 1.0 - g[SIZE-1-y][SIZE-1-x];
					}
				}
		}

	printGrid(grid);

	double sum = 0;
	for (auto v : grid)
		for (auto x : v)
			sum += x;

	printf("sum = %.6f\n", sum);

	getchar();

	return 0;
}
