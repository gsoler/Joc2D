#pragma once

#include <vector>
#include <map>
using namespace std;

class AIEngine
{
private:
	typedef vector<vector<int> > Matrix;
	typedef pair<int, int> PII;
	typedef pair<double, PII> PDII;
	typedef pair<double, PII> Info;
	typedef pair<PII, Info> node;
	typedef pair<PII, double> PIID;
	typedef map<PII, Info>::iterator mapIter;

	double heuristic(const PII& source, const PII& goal);
	void neighbours(PII c, const Matrix& graph, vector<PIID>& nList);
	void getPath(const PII& start, const PII& goal, map<PII, Info>& cSet, vector<PII>& path);

public:

	AIEngine(void);
	~AIEngine(void);
	void aStar(int si, int sj, int gi, int gj, const Matrix& graph, vector<PII>& path);

};

