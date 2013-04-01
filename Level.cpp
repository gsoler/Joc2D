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

	if (metrics.empty()) metrics.push_back(room->getHeight());
	else metrics.push_back(room->getHeight() + metrics.back()+1);

}

int Level::getHeight() 
{
	int h = metrics.back();
	return h;
}

bool Level::collides(int x, int y) {
	int i = 0;
	while (metrics[i] < x) ++i;
	--i;

	return level[i]->collides(x-metrics[i], y);
}

void Level::drawLevel(int bottom, int top)
{
	//check the constrain
	if (bottom < top && bottom >= 0 && top <= metrics.back()) {
		int i = 0;
		while (metrics[i] < bottom) ++i;
		--i;

		int j = i;
		while (metrics[j] < top) ++j;
		--j;

		glPushMatrix();
		glLoadIdentity();

		float T = bottom - metrics[i];
		glTranslatef(0.0f, -T, 0.0f);
		level[i]->drawRoom();

		for (int k = i+1; k <= j; ++k) {
			T = float(metrics[k-1]+1) - T; 
			glTranslatef(0.0f, T, 0.0f);
			level[i]->drawRoom();
		}

		glPopMatrix();
	}
}