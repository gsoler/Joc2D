#include "Level.h"
#include "FieldRoom.h"
#include "MazeRoom.h"

Level::Level(void)
{
	metrics.push_back(0);
}


Level::~Level(void)
{
}

void Level::deleteLevel() 
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
	else if (roomType == MAZE) {
		room = new MazeRoom(heigth, width, bgTileSize, fgTileSize, fgTexId, bgTexId);
	}
	
	room->createRoom();
	level.push_back(room);

	//if (metrics.empty()) metrics.push_back(room->getHeight());
	//else metrics.push_back(room->getHeight() + metrics.back()+1);
	metrics.push_back(room->getHeight() + metrics.back());
}

int Level::getHeight() 
{
	int h = metrics.back();
	return h;
}

bool Level::collides(int x0, int y0, int x1, int y1) {
	int i = 0;
	while (metrics[i] < y0) ++i;
	--i;

	return level[i]->collides(x0-metrics[i], y0, x1 - metrics[i], y1);
}

void Level::drawLevel(int bottom, int top)
{
	//check the constrain
	if (bottom < top && bottom >= 0 && top <= metrics.back()) {
		int i = 0;
		while (metrics[i] < bottom) ++i;

		int j = i;
		while (metrics[j] < top) ++j;

		glPushMatrix();
		glLoadIdentity();

		float T = metrics[i-1] - bottom;
		glTranslatef(0.0f, T, 0.0);

		level[i]->drawRoom();

		for (int k = i+1; k <= j; ++k) { 
			T = level[k-1]->getHeight();
			glTranslatef(0.0f, T, 0.0f);

			level[k]->drawRoom();
		}

		glPopMatrix();
	}
}