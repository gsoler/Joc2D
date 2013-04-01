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
	enum RoomType {FIELD, MAZE};

	Level(void);
	~Level(void);

	void addRoom(int heigth, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId, RoomType roomType);

	void drawLevel(int bottom, int top);
};

