#pragma once

#include<vector>
#include"Room.h"

class Level
{
private:
	typedef std::vector<Room*>::iterator Iter;

	std::vector<Room*> level;
	std::vector<int> metrics;

public:
	static const enum RoomType {FIELD, MAZE};

	Level(void);
	~Level(void);

	void deleteLevel();
	void addRoom(int heigth, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId, RoomType roomType);

	int getHeight();

	bool collides(int x, int y, int xt, int yt);

	void drawLevel(int bottom, int top);
};

