#pragma once

#include<vector>

using namespace std;

class QuickUnionSet
{
private:
	vector<int> id;
	vector<int> sz;

public:
	QuickUnionSet(int n);
	~QuickUnionSet(void);

	int find(int u);
	bool quickUnion(int u, int v);
	int getSize();
};

