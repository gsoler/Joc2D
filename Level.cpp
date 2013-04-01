#include "Level.h"
#include "FieldRoom.h"

Level::Level(void)
{
}


Level::~Level(void)
{
	for (Iter it = level.begin(); it != level.end(); ++it) {
		(*it)->deleteDisplayLists();
		delete *it;
	}
}

void Level::addRoom(int heigth, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId, RoomType roomType) 
{
	Room* room;
	if (roomType == FIELD) {
		room = new FieldRoom(heigth, width, bgTileSize, fgTileSize, fgTexId, bgTexId);
	}
	
	room->createRoom();
	level.push_back(room);
}

void Level::drawLevel(int bottom, int top)
{
	
}