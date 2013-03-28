#include "Maze.h"
//#include <random>
#include "QuickUnionSet.h"
#include <limits>


Maze::Maze(int height, int width, int wallSize, int pathSize)
{
	if (width % 2 == 0) ++width;
	if (height % 2 == 0) ++height;

	this->height = height;
	this->width = width;

	this->wallSize = wallSize;
	this->pathSize = pathSize;

	maze = Matrix(height, vector<int>(width, 0));
}

Maze::~Maze(void)
{
}

void Maze::generateMaze(unsigned int seed) 
{
	vector<int> walls;
	//even cols
	for (int i = 2; i < height-1; i+=2) {
		for (int j = 1; j < width-1; ++j) {
			walls.push_back(width*i+j);
		}
	}
	//even rows
	for (int i = 1; i < height-1; ++i) {
		for (int j = 2; j < width-1; j+=2) {
			if (i % 2 == 1) walls.push_back(width*i+j);
		}
	}

	uniformPermutation(walls, seed);
	
	QuickUnionSet cells((width - 1)/2 * (height - 1)/2);
	
	for (int i = 0; i < walls.size(); ++i) {
		int walli = walls[i] / width;
		int wallj = walls[i] % width;
		
		int cell1,  cell2;

		adjacentCells(walli, wallj, cell1, cell2);

		if (cell1 >= 0) {
			if (cells.quickUnion(cell1, cell2)) walls[i] = -1; //erase wall
		}
	}
	
	for (int i = 0; i < width; ++i) {
		maze[0][i] = 1;
		maze[height-1][i] = 1;
	}

	for (int i = 0; i < height; ++i) {
		maze[i][0] = 1;
		maze[i][width-1] = 1;
	}
	
	for (int i = 0; i < walls.size(); ++i) {
		if (walls[i] >= 0) {
			int walli = walls[i] / width;
			int wallj = walls[i] % width;
			maze[walli][wallj] = 1;
		}
	}
}

int Maze::isWall(int y, int x) {
	return maze[x][y];
}

void Maze::swap(int& x, int& y) {
	int a = x;
	x = y;
	y = a;
}

int Maze::getIdCell(int i, int j) {
	return ((width-1)*(i-1))/4 + (j-1)/2;
}

void Maze::adjacentCells(int walli, int wallj, int& cell1, int& cell2) {
	if (walli % 2 == 0 && wallj % 2 == 1) {
		cell1 = getIdCell(walli+1, wallj);
		cell2 = getIdCell(walli-1, wallj);
	}
	else if (walli % 2 == 1 && wallj % 2 == 0) {
		cell1 = getIdCell(walli, wallj+1);
		cell2 = getIdCell(walli, wallj-1);
	}
	else {
		cell1 = -1;
		cell2 = -1;
	}
}

void Maze::uniformPermutation(vector<int>& v, unsigned int seed) {

	//default_random_engine generator(seed);
	//uniform_int_distribution<int> distribution;

	for (int i = 0; i < v.size(); ++i) {
		//int p = distribution(generator);
		int p = rand();
		p %= v.size() - i;

		swap(v[i], v[p+i]);
	}
}
