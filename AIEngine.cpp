#include "AIEngine.h"
#include <queue>



AIEngine::AIEngine(void)
{
}

AIEngine::~AIEngine(void)
{
}

double AIEngine::heuristic(const PII& source, const PII& goal)
{
	double di = goal.first - source.first;
	double dj = goal.second - source.second;

	return sqrt(di*di+dj*dj);
}

void AIEngine::neighbours(PII c, const Matrix& graph, vector<PIID>& nList) 
{
	int n = graph.size();
	int m = graph[0].size();

	int ai[8] = { 1,1,1,0, 1,-1,-1, 0};
	int aj[8] = {-1,0,1,1,-1, 0,-1,-1};

	int i = c.first;
	int j = c.second;

	for (int k = 0; k < 8; ++k) {
		int ni = i+ai[k];
		int nj = j+ai[k];

		if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
			if (graph[ni][nj] == 0) {
				
				double dai = abs(ai[k]);
				double daj = abs(aj[k]);

				double dist = sqrt(dai + daj);

				nList.push_back(PIID(PII(ni, nj), dist));
			}
		}
	}
}

void AIEngine::getPath(const PII& start, const PII& goal, map<PII, Info>& cSet, vector<PII>& path) {
	PII current = goal;
	while (current != start) {
		path.push_back(current);
		current = cSet[current].second;
	}
}

void AIEngine::aStar(int si, int sj, int gi, int gj, const Matrix& graph, vector<PII>& path) 
{
	PII start(si, sj);
	PII goal(gi, gj);

	//priority queue "sorted" by f = g+h
	priority_queue<PDII> openQueue;
	//maps where the key is the node id and the value is g
	map<PII, Info> openSet;
	map<PII, Info> closedSet;

	//set first node
	double h = heuristic(start, goal);
	openQueue.push(PDII(h, start));
	openSet[start] = PDII(0.0, start);

	while (!openQueue.empty()) {
		PII current = openQueue.top().second; 
		openQueue.pop();

		if (current == goal) {
			closedSet[current] = openSet[current];
			getPath(start, goal, closedSet, path);
			return;
		}
		
		//in order to modify a node g value, another copy of the node is
		//pushed into the openQueue so the best value will be extracted 
		//first. Thus, we need to check if the node extracted is already 
		//closed and, in that case, draw another node from de queue.
		
		mapIter it = closedSet.find(current);
		if (it == closedSet.end()) {

			//move current node from openSet to closedSet and keep de g value 
			//for further usage
			it = openSet.find(current);
			double g = it->second.first;
			closedSet.insert(*it);
			openSet.erase(it);
		
			vector<PIID> nList;
			neighbours(current, graph, nList);

			for (int i = 0; i < nList.size(); ++i) {
				PII neighbour = nList[i].first;
				double dist = nList[i].second; 

				it = closedSet.find(neighbour);
				//if neightbour is not closed
				if (it == closedSet.end()) {
					double tg = g + dist;
					
					it = openSet.find(neighbour);
					//if neightbour is not open
					if (it == openSet.end())  {
						openSet[neighbour] = Info(tg, current);
						double f = tg + heuristic(neighbour, goal);
						openQueue.push(PDII(f, neighbour));
					}
					//if is open but tentative g is better than previous g
					else if (tg < it->second.first) {
						it->second = Info(tg, current);
						double f = tg + heuristic(neighbour, goal);
						//note that we may duplicate nodes
						openQueue.push(PDII(f, neighbour));
					}
				}
			}
		}
	}
}
