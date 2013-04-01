#pragma once

#include <vector>
#include <gl/glut.h>

class Room
{
protected:
	typedef std::vector<std::vector<int> > Matrix;

	int width;
	int height;

	int bgTileSize;
	int fgTileSize;

	GLuint fgTexId;
	GLuint bgTexId;

	GLuint fgDisplayList;
	GLuint bgDisplayList;

	Matrix collisonMap;

public:
	Room(int height, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId);
	virtual ~Room(void);

	int getWidth(void);
	int getHeight(void);

	bool collides(int x, int y);

	virtual void createRoom(void) = 0;

	void drawRoom(void);

	void deleteDisplayLists();
};

