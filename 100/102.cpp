// https://projecteuler.net/problem=102
// Triangle containment

#include <iostream>
#include <fstream>

using namespace std;

struct pt {
	int x, y;
};

int cross(const pt& A, const pt& B) {
	return A.x*B.y - A.y*B.x;
}

long sgn(long a) {
	if (a > 0)
		return 1;
	if (a < 0)
		return -1;

	return 0;
}

bool test(const pt& A, const pt& B, const pt& C) {
	pt AB, AC, BC;

	AB.x = A.x - B.x;
	AB.y = A.y - B.y;
	
	AC.x = A.x - C.x;
	AC.y = A.y - C.y;

	BC.x = B.x - C.x;
	BC.y = B.y - C.y;

	if (sgn(cross(AB, A)) * sgn(cross(AC, A)) > 0)
		return false;

	if (sgn(cross(AB, B)) * sgn(cross(BC, B)) < 0)
		return false;

	return true;
}

int main(int argc, char* argv[]) {	
	ifstream fin("p102_triangles.txt");
	pt A, B, C;
	char comma;

	unsigned int count = 0;
	while(fin.good()) {
		fin >> A.x >> comma >> A.y >> comma >> B.x >> comma >> B.y >> comma >> C.x >> comma >> C.y;

		if (test(A, B, C))
			count++;
	}

	printf("count = %d\n", count);
	
	getchar();

	return 0;
}
