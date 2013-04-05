#pragma once

#include<vector>
#include"Room.h"

class Level
{
private:
	typedef std::vector<Room*>::iterator Iter;

	std::vector<Room*> level;
	std::vector<int> metrics;

	int getRoom(int start, int end);

public:
	static const enum RoomType {FIELD, MAZE, MMAZE};

	Level(void);
	~Level(void);

	void deleteLevel();

	void addRoom(int heigth, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId, RoomType roomType);
	void addBullet(int x, int y, int d);
	void addEnemy(int x, int y, Room::EnemyType t);

	int getHeight();

	int collides(int x, int y, int xt, int yt);
	bool collidesMap(int x, int y);
	int process(int x0, int y0, int x1, int y1);

	void drawLevel(GLuint texBullets, GLuint texShooter, GLuint texKamikaze);
	//void drawLevel(int bottom, int top);
};

