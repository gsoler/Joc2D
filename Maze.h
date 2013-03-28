#pragma once

#include <vector>

using namespace std;


class Maze
{

typedef vector<vector<int> > Matrix;

private:
	int height;
	int width;

	int wallSize;
	int pathSize;
	
	Matrix maze;
	
	void swap(int& x, int&y);
	void uniformPermutation(vector<int>& v, unsigned int seed);
	void adjacentCells(int walli, int wallj, int& cell1, int& cell2);
	int getIdCell(int i, int j);	

public:
	Maze(int height, int width, int wallSize, int pathSize);
	~Maze(void);
	void generateMaze(unsigned int seed);
	int isWall(int x, int y);
};

