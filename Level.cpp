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

	if (metrics.empty()) metrics.push_back(room->getHeigth());
	else metrics.push_back(room->getHeigth() + metrics.back()+1);

}

void Level::drawLevel(int bottom, int top)
{
	if (bottom < top && bottom >= 0 && top <= metrics.back()) {
		int i = 0;
		while (metrics[i] < bottom) ++i;
		--i;

		int j = i;
		while (metrics[j] < top) ++j;
		--j;

		for (int k = i; k <= j; ++k) {

		}
	}
}