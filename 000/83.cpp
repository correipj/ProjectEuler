// https://projecteuler.net/problem=83
// Path sum: four ways

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <array>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
	ifstream fin("p083_matrix.txt");

	const int SIZE = 80;
	
	vector<vector<unsigned long> > mat;	
	vector<vector<unsigned long> > sum;	
	for (int i = 0; i < SIZE; i++) {
		mat.push_back(vector<unsigned long>(SIZE));
		sum.push_back(vector<unsigned long>(SIZE, -1)); 
	}
	
	queue<pair<unsigned int, unsigned int> > Q;
	
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++) {
			char comma;
			if (j)	fin >> comma;
			fin >> mat[i][j];
			//Q.push(make_pair(i, j));
		}
	fin.close();

	sum[0][0] = mat[0][0];
	Q.push(make_pair(0, 0));

	// Djikstra
	array<int, 4> xDirs = {-1, 0, 0, 1};
	array<int, 4> yDirs = {0, -1, 1, 0};
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


	printf("sum = %d\n", sum.back().back());

	getchar();

	return 0;
}

