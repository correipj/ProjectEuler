// https://projecteuler.net/problem=81
// Path sum: two ways

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
	ifstream fin("p081_matrix.txt");

	const int SIZE = 80;
	
	vector<vector<unsigned long> > mat;	
	vector<vector<unsigned long> > sum;
	for (int i = 0; i < SIZE; i++) {
		mat.push_back(vector<unsigned long>(SIZE));
		sum.push_back(vector<unsigned long>(SIZE));
	}

	char comma;
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++) {
			if (j)	fin >> comma;
			fin >> mat[i][j];
		}
	fin.close();

	// Find min sum of adjacent cells
	for (int i = 0; i < 2*SIZE; i++)
		for (int j = 0; j <= i; j++) {
			int x = i-j;
			int y = j;

			if (x >= SIZE || y >= SIZE)
				continue;

			if (x == 0 && y == 0) {
				sum[0][0] = mat[0][0];
				continue;
			}
			
			if (x == 0) {
				sum[y][x] = mat[y][x] + sum[y-1][x];
				continue;
			}
			if (y == 0) {
				sum[y][x] = mat[y][x] + sum[y][x-1];
				continue;
			}

			sum[y][x] = mat[y][x] + min(sum[y-1][x], sum[y][x-1]);
		}

	printf("sum = %lu\n", sum.back().back());	

	getchar();

	return 0;
}

