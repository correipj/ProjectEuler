// https://projecteuler.net/problem=82
// Path sum: three ways

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <array>
#include <algorithm>

using namespace std;


const int SIZE = 80;
vector<vector<unsigned long> > mat;	

// This problem could probably be solved a lot quicker by implementing the
// Floyd-Warshall algorithm rather than performing djikstra N times

unsigned long djikstra(unsigned int startY) {	
	vector<vector<unsigned long> > sum;	

	for (int i = 0; i < SIZE; i++)
		sum.push_back(vector<unsigned long>(SIZE, -1));

	sum[startY][0] = mat[startY][0];

	// Only move up/down/right
	array<int, 3> xDirs = {0, 0, 1};
	array<int, 3> yDirs = {-1, 1, 0};

	queue<pair<unsigned int, unsigned int> > Q;
	Q.push(make_pair(startY, 0));

	// Djikstra
	while(!Q.empty()) {
		unsigned int i = Q.front().first;
		unsigned int j = Q.front().second;
		Q.pop();

		unsigned int currSum = sum[i][j];

		for (int d = 0; d < xDirs.size(); d++) {
			int dx = xDirs[d];
			int dy = yDirs[d];

			if (j + dx < 0 || j + dx >= SIZE)
				continue;
			if (i + dy < 0 || i + dy >= SIZE)
				continue;

			unsigned long dirSum = sum[i+dy][j+dx];
			unsigned long matDir = mat[i+dy][j+dx];

			if (dirSum == -1 || currSum + matDir < dirSum) {
				sum[i+dy][j+dx] = currSum + matDir;
				Q.push(make_pair(i+dy, j+dx));
			}
		}
	}

	unsigned long minSumRight = 9999999;
	for (int i = 0; i < SIZE; i++)
		minSumRight = min(minSumRight, sum[i].back());

	return minSumRight;
}

int main(int argc, char* argv[]) {
	for (int i = 0; i < SIZE; i++)
		mat.push_back(vector<unsigned long>(SIZE));	

	ifstream fin("p082_matrix.txt");
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++) {
			char comma;
			if (j)	fin >> comma;
			fin >> mat[i][j];
		}
	fin.close();

	unsigned long minSum = 9999999;
	for (int startY = 0; startY < SIZE; startY++)
		minSum = min(minSum,  djikstra(startY));

	printf("sum = %d\n", minSum);

	getchar();

	return 0;
}

