// https://projecteuler.net/problem=96
// Sudoku

// This one is gonna be a P.I.T.A.

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <map>

using namespace std;

class pos_t {
public:
	pos_t() {
		for(int i = 0; i < 9; i++)
			solns[i] = 0;
	}
	pos_t(const pos_t& p) {
		solns = p.solns;
	}

	pos_t& operator=(const pos_t& p) {
		solns = p.solns;

		return *this;
	}

	bool isSolved() const {
		int count = 0;
		for (int i = 0; i < 9; i++)
			if (solns[i]) {
				if (count == 1)
					return false;

				count++;
			}

		return count == 1;
	}
	unsigned int val() const {
		if (isSolved()) {
			for (int i = 0; i < 9; i++)
				if (solns[i])
					return i;
		} else
			return 0;
	}
	void setVal(unsigned int v) {
		for(int i = 0; i < 9; i++)
			solns[i] = 0;
		solns[v] = 1;
	}

	array<bool, 9> solns;
};

typedef array<array<pos_t, 9>, 9> grid_t;

bool isGridSolved(const grid_t& g) {
	for(int r = 0; r < 9; r++)
		for (int c = 0; c < 9; c++)
			if (g[r][c].isSolved() == false)
				return false;

	return true;
}

// Search grid for a square where no numbers are valid, this grid is invalid
bool isGridValid(const grid_t& g) {
	for(int r = 0; r < 9; r++)
		for (int c = 0; c < 9; c++) {
			bool foundPossibility = false;
			for (int i = 0; i < 9; i++)
				if (g[r][c].solns[i]) {
					foundPossibility = true;
					break;
				}

			if (!foundPossibility)
				return false;
		}

	return true;
}

pos_t solveGridPos(const grid_t& g, unsigned int r, unsigned int c) {
	if (g[r][c].isSolved())
		return g[r][c];

	// Assume all numbers are valid, eliminate those that aren't
	pos_t p;
	for (int i = 0; i < 9; i++)
		p.solns[i] = 1;
	
	// Check along row
	for (int y = 0; y < 9; y++)
		if (g[y][c].isSolved())
			p.solns[g[y][c].val()] = 0;
		
	// Check along column
	for (int x = 0; x < 9; x++)
		if (g[r][x].isSolved())
			p.solns[g[r][x].val()] = 0;
	
	// Check in 3x3 square
	for (int x = 3*(c/3); x < 3+3*(c/3); x++)
		for (int y = 3*(r/3); y < 3+3*(r/3); y++)
			if (g[y][x].isSolved())
				p.solns[g[y][x].val()] = 0;

	return p;
}

// returns 3 top left digits of solved grid
unsigned int solve(grid_t& g) {
	bool solvedSpace;

	do {
		solvedSpace = false;

		// Find forced values, ie squares where only one possible value exists
		for (int r = 0; r < 9; r++) {
			for (int c = 0; c < 9; c++) {
				if (g[r][c].isSolved())
					continue;

				g[r][c] = solveGridPos(g, r, c);

				if (g[r][c].isSolved())
					solvedSpace = true;
			}
		}

		// Find a rows/cols/squares for which a value can only go in one square
		// rows
		for (int r = 0; r < 9; r++) {
			for (int n = 0; n < 9; n++) {
				int nPos = 0;
				bool foundSolvedN = false;

				// count number of squares where n can fit
				for (int c = 0; c < 9; c++)
					if (g[r][c].solns[n]) {
						if (g[r][c].isSolved())
							foundSolvedN = true;
						else
							nPos++;
					}

				if (nPos != 1 || foundSolvedN)
					continue;

				// n can only fit in one space
				for (int c = 0; c < 9; c++)
					if (g[r][c].solns[n]) {
						g[r][c].setVal(n);
						solvedSpace = true;
						break;
					}
			}
		}
		// cols
		for (int c = 0; c < 9; c++) {
			for (int n = 0; n < 9; n++) {
				int nPos = 0;
				bool foundSolvedN = false;

				// count number of squares where n can fit
				for (int r = 0; r < 9; r++)
					if (g[r][c].solns[n]) {
						if (g[r][c].isSolved())
							foundSolvedN = true;
						else
							nPos++;
					}

				if (nPos != 1 || foundSolvedN)
					continue;

				// n can only fit in one space
				for (int r = 0; r < 9; r++)
					if (g[r][c].solns[n]) {
						g[r][c].setVal(n);
						solvedSpace = true;
						break;
					}
			}
		}
		// squares
		for (int sr = 0; sr < 9; sr += 3) {
			for (int sc = 0; sc < 9; sc += 3) {
				for (int n = 0; n < 9; n++) {
					int nPos = 0;
					bool foundSolvedN = false;

					// count number of squares where n can fit
					for (int dr = 0; dr < 3; dr++)
						for (int dc = 0; dc < 3; dc++)
							if (g[sr+dr][sc+dc].solns[n]) {
								if (g[sr+dr][sc+dc].isSolved())
									foundSolvedN = true;
								else
									nPos++;
							}

					if (nPos != 1 || foundSolvedN)
						continue;

					// n can only fit in one space
					for (int dr = 0; dr < 3; dr++)
						for (int dc = 0; dc < 3; dc++)
							if (g[sr+dr][sc+dc].solns[n]) {
								g[sr+dr][sc+dc].setVal(n);
								solvedSpace = true;
								break;
							}
				}
			}
		}

		if (!isGridValid(g))
			return 0;
	} while(solvedSpace == true);

	if (isGridSolved(g) == false) {
		// Brute force a solution
		// Find square with least # of possibilities
		unsigned int minN = 9;
		unsigned int minR, minC;
		for (int r = 0; r < 9; r++)
			for (int c = 0; c < 9; c++) {
				int count = 0;
				for (int n = 0; n < 9; n++)
					if (g[r][c].solns[n])
						count++;

				if (count > 1 && count < minN) {
					minN = count;
					minR = r;
					minC = c;
				}
			}

		vector<unsigned int> vals;
		for (int n = 0; n < 9; n++)
			if (g[minR][minC].solns[n])
				vals.push_back(n);

		// Replace square with a possible value
		// if solution is invalid, try next one
		// if solution is valid, it is the only solution (maybe idk)
		for (auto v : vals) {
			grid_t newG = g;
			newG[minR][minC].setVal(v);

			unsigned int soln = solve(newG);

			if (soln != 0)
				return soln;
		}

		// If none of those possible values returned a valid solution, perhaps
		// grid wasn't valid
		return 0;
	}

	return 100*(g[0][0].val() + 1) + 10*(g[0][1].val() + 1) + (g[0][2].val() + 1);
}

int main(int argc, char* argv[]) {
	ifstream fin("p096_sudoku.txt");

	unsigned int sum = 0;
	int i = 0;

	while(fin.good()) {
		i++;
		string gridNumStr;
		getline(fin, gridNumStr);

		grid_t g;
		unsigned char inChar;

		for (int r = 0; r < 9; r++) {
			for (int c = 0; c < 9; c++) {
				fin >> inChar;

				if (inChar != '0')
					g[r][c].solns[inChar-'1'] = true;
			}
		}

		// read newline
		fin >> inChar;

		sum += solve(g);
	}

	fin.close();

	printf("sum = %u\n", sum);


	getchar();

	return 0;
}
