#include "MovingMazeRoom.h"


MovingMazeRoom::MovingMazeRoom(int heigth, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId)
	: MazeRoom(heigth, width, bgTileSize, fgTileSize, fgTexId,bgTexId)
{
	processable = true;
}


MovingMazeRoom::~MovingMazeRoom(void)
{
}

void MovingMazeRoom::createRoom(void) 
{
	MazeRoom::createRoom();

	int n = collisonMap.size();

	
}

void MovingMazeRoom::procces(void) 
{
	
}