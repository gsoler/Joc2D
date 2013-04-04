#include "Room.h"


Room::Room(int height, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId)
{
	this->height = height;
	this->width = width;

	this->bgTileSize = bgTileSize;
	this->fgTileSize = fgTileSize;
	
	this->fgTexId = fgTexId;
	this->bgTexId = bgTexId;

	processable = false;
}


Room::~Room(void)
{
}

int Room::getWidth(void) 
{
	return width;
}

int Room::getHeight(void)  
{
	return height;
}

bool Room::isProcessable(void) 
{
	return processable;
}

bool Room::collides(int x0, int y0, int x1, int y1) 
{
	if (x0 < 0 || x0 > width || y0 < 0 || y0 > height) return true; 
	
	int tx = x0/fgTileSize;
	int ty = y0/fgTileSize;
	bool d = (collisonMap[ty][tx] != 0);
	return d;
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