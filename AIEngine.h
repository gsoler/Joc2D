#pragma once

#include <vector>
using namespace std;

class AIEngine
{
private:
	typedef vector<vector<int> > Matrix;
	typedef pair<int, int> PII;
	typedef pair<double, PII > PDII; 
	typedef pair<PII, double> PIID; 
	typedef map<PII, double>::iterator mapIter;

	double heuristic(const PII& source, const PII& goal);
	void neighbours(PII c, const Matrix& graph, vector<PIID>& nList);

public:

	AIEngine(void);
	~AIEngine(void);
	void aStar(int si, int sj, int gi, int gj, const Matrix& graph, int& path);

};

