#include "QuickUnionSet.h"

QuickUnionSet::QuickUnionSet(int n)
{
	this->sz = vector<int>(n,0);

	this->id = vector<int>(n);
	for (int i = 0; i < n; ++i) id[i] = i;
}


QuickUnionSet::~QuickUnionSet(void)
{
}

int QuickUnionSet::find(int u) 
{
	while (u != id[u]) {
		id[u] = id[id[u]];
		u = id[u];
	}

	return u;
}

bool QuickUnionSet::quickUnion(int u, int v) 
{
	int i = find(u);
	int j = find(v);

	if (i == j) return false;

	if (sz[i] > sz[j]) {
		id[j] = i;
		sz[i] += sz[j];
	}
	else {
		id[i] = j;
		sz[j] += sz[i];
	}

	return true;
}

int QuickUnionSet::getSize(void) 
{
	return id.size();
}