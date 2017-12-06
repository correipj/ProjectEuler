// https://projecteuler.net/problem=91

#include <iostream>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

struct pt {
public:
	pt(int xx = 0, int yy = 0) {
		x = xx;
		y = yy;
	}

	// Compare by x first, then y
	bool operator<(const pt& rhs) const {
		return (x < rhs.x) || (x == rhs.x && y < rhs.y);
	}

	int x, y;
};

pt trans(const pt& p) {
	return pt(p.y, p.x);
}

map<pt, set<pt> > checkedPts;

void add(const pt& A, const pt& B) {
	const pt minPt = min(A, B);
	const pt maxPt = max(A, B);

	if (checkedPts.count(minPt) == 0)
		checkedPts[minPt] = set<pt>();
	
	checkedPts[minPt].insert(maxPt);
}

bool check(const pt& A, const pt& B) {
	//printf("check (%d, %d)  (%d, %d)", A.x, A.y, B.x, B.y);

	// Search for right angle in triangle OAB
	const pt AB(B.x - A.x, B.y - A.y);
					
	const int dot1 = A.x*AB.x + A.y*AB.y;
	const int dot2 = B.x*AB.x + B.y*AB.y;
	const int dot3 = A.x*B.x + A.y*B.y;

	if (dot1 != 0 && dot2 != 0 && dot3 != 0) {
		//printf(" - not right triangle\n");
		return false;
	}

	// Check if triangle OAB has already been found
	const pt minPt = min(A, B);
	const pt maxPt = max(A, B);

	// Check if any triangles have been found containing min(A, B);
	if (checkedPts.count(minPt) == 0) {
		add(A, B);
		//printf(" - is good  1\n");
		return true;
	}

	// Check if these triangles with min(A, B) also contain max(A, B);
	if (checkedPts[minPt].count(maxPt) == 0) {
		add(A, B);
		//printf(" - is good  2\n");
		return true;
	}
	
	
	//printf(" - already found\n");

	return false;
}

int main(int argc, char* argv[]) {
	unsigned int N = 50;
	unsigned int count = 0;

	for (pt a(0, 1); a.y <= N; a.y++)
		for (a.x = 0; a.x <= a.y; a.x++)
			for(pt b(0, 0); b.y <= N; b.y++)
				for(b.x = 0; b.x <= N; b.x++) {
					// Don't check origin
					if(b.x == 0 && b.y == 0)
						continue;

					// Don't check A == B
					if (a.x == b.x && a.y == b.y)
						continue;

					if(check(a, b))
						count++;

					// check symmetry of (a, b)
					if (check(trans(a), trans(b)))
						count++;
				}

	printf("%d  triangles on a grid on coordinates between 0 and %d\n", count, N);
	
	getchar();

	return 0;
}

