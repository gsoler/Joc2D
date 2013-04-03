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
	virtual ~MazeRoom(void);

	virtual void createRoom(void);
};

