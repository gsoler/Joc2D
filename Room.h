#pragma once

#include <vector>
#include <gl/glut.h>

class Room
{
protected:
	typedef std::vector<std::vector<int> > Matrix;

	bool processable;

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

	bool isProcessable(void);

	bool collides(int x, int y, int tx, int ty);

	virtual void createRoom(void) = 0;

	void drawRoom(void);

	void deleteDisplayLists(void);
};

