#pragma once
#include "Room.h"
class MazeRoom :
	public Room
{
private:
	void createBackground(void);
	void createForeground(void);

public:
	MazeRoom(int heigth, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId);
	~MazeRoom(void);

	void createRoom(void);
};

