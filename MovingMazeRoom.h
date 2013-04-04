#pragma once
#include "MazeRoom.h"
#include <vector>

class MovingMazeRoom : public MazeRoom
{
private:
	typedef std::pair<double, double> Vec2;
	typedef std::vector<Vec2>::iterator Iter;
	std::vector<Vec2> blocks;

	void drawBlock(Vec2 b);

public:
	MovingMazeRoom(int heigth, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId);
	~MovingMazeRoom(void);

	void createRoom(void);

	void drawRoom(void);

	void procces(void);
};

