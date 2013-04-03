#pragma once
#include "MazeRoom.h"
#include <vector>

class MovingMazeRoom : public MazeRoom
{
private:
	struct vec2 {
		double x;
		double y;
	};

	std::vector<vec2> blocks;

public:
	MovingMazeRoom(int heigth, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId);
	~MovingMazeRoom(void);

	void createRoom(void);

	void procces(void);
};

