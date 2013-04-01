#include "Room.h"


Room::Room(int height, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId)
{
	this->heigth = height;
	this->width = width;

	this->bgTileSize = bgTileSize;
	this->fgTileSize = fgTileSize;
	
	this->fgTexId = fgTexId;
	this->bgTexId = bgTexId;
}


Room::~Room(void)
{
}

int Room::getWidth(void) 
{
	return width;
}

int Room::getHeigth(void)  
{
	return heigth;
}

bool Room::collides(int x, int y) 
{
	if (x < 0 || x > width || y < 0 || y > heigth) return true; 
	
	int tx = x/fgTileSize;
	int ty = y/fgTileSize;

	return (collisonMap[ty][tx] != 0);
}

void Room::drawRoom() 
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, bgTexId);
	glCallList(bgDisplayList);

	glBindTexture(GL_TEXTURE_2D, fgTexId);
	glCallList(fgDisplayList);

	glDisable(GL_TEXTURE_2D);
}

void Room::deleteDisplayLists()
{
	glDeleteLists(bgDisplayList, 1);
	glDeleteLists(fgDisplayList, 1);
}