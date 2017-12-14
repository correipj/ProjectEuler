// https://projecteuler.net/problem=107
// Minimal network

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <functional>

using namespace std;

typedef vector<vector<int> > net_t;

struct edge_t {
	int a, b;
	int w;

	bool operator>(const edge_t& rhs) const {
		return w > rhs.w;
	}
};

unsigned int sumNet(const net_t& n) {
	unsigned int sum = 0;
	for (int i = 0; i < n.size(); i++)
		for (int j = 0; j < i; j++)
			sum += n[i][j];

	return sum;
}


int main(int argc, char* argv[]) {
	ifstream fin("p107_network.txt");

	net_t net;
	while(fin.good()) {
		net.push_back(vector<int>());

		char temp;
		do {
			net.back().push_back(0);

			if (fin.peek() == '-')
				fin.get(temp);
			else
				fin >> net.back().back();

			fin.get(temp);
		} while(temp == ',');
	}
	fin.close();

	unsigned long oldSum = sumNet(net);

	// Prim's algorithm

	// Initialize new tree with a single vertex
	net_t tree(net.size(), vector<int>(net.size(), 0));
	set<int> verts;
	verts.insert(0);

	// Initialize queue of edges to check. Start with all edges coming from initial node
	priority_queue<edge_t, vector<edge_t>, greater<edge_t> > Q;
	for (int i = 1; i < net.size(); i++) {
		if (net[0][i] == 0)
			continue;

		edge_t e;
		e.a = 0;
		e.b = i;
		e.w = net[0][i];

		Q.push(e);
	}

	while(!Q.empty()) {
		edge_t e = Q.top();
		Q.pop();

		// If edge already connects to solved tree
		if (verts.count(e.b))
			continue;
		
		// If not, add it to the tree
		verts.insert(e.b);
		tree[e.a][e.b] = tree[e.b][e.a] = e.w;

		// Add all edges from current point
		for (int i = 0; i < net.size(); i++) {
			if (i == e.b || net[e.b][i] == 0)
				continue;

			edge_t newE;
			newE.a = e.b;
			newE.b = i;
			newE.w = net[e.b][i];

			Q.push(newE);
		}
	}

	unsigned int newSum = sumNet(tree);

	printf("%d - %d  =  %d savings\n", oldSum, newSum, oldSum - newSum);
	
	getchar();

	return 0;
}
