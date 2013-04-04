#pragma once

#include <vector>
#include <gl/glut.h>
#include "cShot.h"

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

	//std::vector<Enemy*> enemies;
	//std::vector<cShot> bullets;

	void processBullet(int i);
	void processEnemy(int i);

public:
	Room(int height, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId);
	virtual ~Room(void);

	int getWidth(void);
	int getHeight(void);

	bool isProcessable(void);

	bool collides(int x, int y, int tx, int ty);

	virtual void createRoom(void) = 0;

	virtual void drawRoom(void);

	void deleteDisplayLists(void);

	void addEnemy(int x, int y);
	void addBullet(int x, int y);

	virtual void process(int x1, int y1, int x2, int y2); 
};

