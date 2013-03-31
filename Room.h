#pragma once

#include <vector>
#include <gl/glut.h>

class Room
{
protected:
	typedef std::vector<std::vector<int> > Matrix;

	int width;
	int heigth;

	int bgTileSize;
	int fgTileSize;

	GLuint fgTexId;
	GLuint bgTexId;

	GLuint fgDisplayList;
	GLuint bgDisplayList;

	Matrix collisonMap;

public:
	Room(int heigth, int width, int bgTileSize, int fgTileSize, int fgTexId, int bgTexId);
	virtual ~Room(void);

	virtual int getWidth(void);
	virtual int getHeigth(void);

	virtual bool collides(int x, int y);

	virtual void createRoom(void) = 0;

	virtual void drawRoom(void);
};

