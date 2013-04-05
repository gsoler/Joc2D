#include "Level.h"
#include "FieldRoom.h"
#include "MazeRoom.h"
#include "MovingMazeRoom.h"

Level::Level(void)
{
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
	else if (roomType == MMAZE) {
		room = new MovingMazeRoom(heigth, width, bgTileSize, fgTileSize, fgTexId, bgTexId);
	}
	
	room->createRoom();
	level.push_back(room);

	if (metrics.empty()) metrics.push_back(room->getHeight());
	else metrics.push_back(room->getHeight() + metrics.back() + 1);
	//metrics.push_back(room->getHeight() + metrics.back() + 1);
}

int Level::getHeight() 
{
	int h = metrics.back();
	return h;
}

int Level::getRoom(int start, int h) 
{
	int i = start;
	while (i < metrics.size() && metrics[i] <= h) ++i;

	if (i >= metrics.size()) return -1;

	return i;
}

int Level::collides(int x0, int y0, int x1, int y1) 
{
	int i = getRoom(0, y0);
	if (i < 0) return 1;

	int offset = metrics[i] - level[i]->getHeight();
	return level[i]->collides(x0, y0 - offset, x1, y1 - offset);
}

bool Level::collidesMap(int x, int y) 
{
	int i = getRoom(0, y);
	if (i < 0) return false;

	int offset = metrics[i] - level[i]->getHeight();
	return level[i]->collidesMap(x, y - offset);
}


void Level::addBullet(int x, int y, int d) 
{
	int i = getRoom(0, y);
	int offset = metrics[i] - level[i]->getHeight();

	level[i]->addBullet(x, y - offset, d);

}

void Level::addEnemy(int x, int y, Room::EnemyType t) {
	int i = getRoom(0, y);
	int offset = metrics[i] - level[i]->getHeight();

	level[i]->addEnemy(x, y - offset, t);
}

int Level::process(int x0, int y0, int x1, int y1)
{
	int i = getRoom(0, y0);
	int offset = metrics[i] - level[i]->getHeight();

	if (i < 0) return 1;
	return level[i]->process(x0, y0 - offset, x1, y1 - offset);
}

/*
void Level::drawLevel(int bottom, int top)
{
	//check the constrain
	if (bottom < top && bottom >= 0 && top <= metrics.back()) {
		int i = getRoom(0, bottom);
		int j = getRoom(i, top);

		glPushMatrix();
		glLoadIdentity();

		float T = 0.0f;

		if (i > 0) T = metrics[i-1] - bottom; 
		else T = bottom;

		glTranslatef(0.0f, -T, 0.0);

		level[i]->drawRoom();

		for (int k = i+1; k <= j; ++k) { 
			T = level[k-1]->getHeight();
			glTranslatef(0.0f, T, 0.0f);

			level[k]->drawRoom();
		}

		glPopMatrix();
	}
}*/

void Level::drawLevel(GLuint texBullets, GLuint texShooter, GLuint texKamikaze) 
{
	glPushMatrix();

	float T = 0.0f;
	for (int i = 0; i < level.size(); ++i) {
		glTranslatef(0.0f, T, 0.0f);

		level[i]->drawRoom(texBullets, texShooter, texKamikaze);
		T = level[i]->getHeight();
	}

	glPopMatrix();
}