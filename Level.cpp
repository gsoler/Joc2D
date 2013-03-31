#include "Level.h"
#include "FieldRoom.h"

Level::Level(void)
{
}


Level::~Level(void)
{
	for (Iter it = level.begin(); it != level.end(); ++it) {
		delete *it;
	}
}

void Level::addRoom(int heigth, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId, RoomType roomType) 
{
	Room* room;
	if (roomType == FIELD) {
		room = new FieldRoom(heigth, width, bgTileSize, fgTileSize, fgTexId, bgTexId);
	}

	level.push_back(room);
}