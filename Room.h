#pragma once

#include <vector>
#include <gl/glut.h>
#include "cShot.h"
#include "Enemy.h"

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

	std::vector<Enemy> shooters;
	std::vector<Enemy> kamikazes;
	std::vector<cShot> bullets;

	void processBullet(int i);
	void processShooter(int i, int x1, int y1, int x2, int y2);
	void processKamikazes(int i, int x1, int y1, int x2, int y2);

public:

	static const enum EnemyType{SHOOTER, KAMIKAZE};

	Room(int height, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId);
	virtual ~Room(void);

	int getWidth(void);
	int getHeight(void);

	bool collides(int x, int y, int tx, int ty);

	virtual void createRoom(void) = 0;

	virtual void drawRoom(void);

	void deleteDisplayLists(void);

	void addEnemy(int x, int y, EnemyType t);
	void addBullet(int x, int y, int d);

	virtual void process(int x1, int y1, int x2, int y2); 
};

