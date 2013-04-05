#include "Room.h"

Room::Room(int height, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId)
{
	this->height = height;
	this->width = width;

	this->bgTileSize = bgTileSize;
	this->fgTileSize = fgTileSize;
	
	this->fgTexId = fgTexId;
	this->bgTexId = bgTexId;
}


Room::~Room(void)
{
}

int Room::getWidth(void) 
{
	return width;
}

int Room::getHeight(void)  
{
	return height;
}

int Room::collides(int x0, int y0, int x1, int y1) 
{

	int x, y;
	int w, h;
	
	for (int i = 0; i < bullets.size(); ++i) {
		if (bullets[i].GetState() == STATE_SHOTING) {
			bullets[i].getPosition(&x, &y);
			bullets[i].getDimensions(&w, &h);

			if (boxCollision(x0, y0, x1, y1, x, y, x+w, y+h)) {
				return 2;
			}
		}
	}

	for (int i = 0; i < kamikazes.size(); ++i) {
		if (kamikazes[i].isAlive()) {
			kamikazes[i].GetPosition(&x, &y);
			kamikazes[i].GetWidthHeight(&w, &h);
		
			if (boxCollision(x0, y0, x1, y1, x, y, x+w, y+h)) {
				return 2;
			}
		}
	}

	for (int i = 0; i < shooters.size(); ++i) {
		if (shooters[i].isAlive()) {
			shooters[i].GetPosition(&x, &y);
			shooters[i].GetWidthHeight(&w, &h);
			if (boxCollision(x0, y0, x1, y1, x, y, x+w, y+h)) {
				return 2;
			}
		}
	}
}

bool Room::collidesMap(int x, int y)
{
	int tx = x/fgTileSize;
	int ty = y/fgTileSize;

	if (ty >=  collisonMap.size()) return true;
	return (collisonMap[ty][tx] != 0);
}


void Room::addEnemy(int x, int y, EnemyType t) 
{
	if (t == SHOOTER) {
		shooters.push_back(Enemy());
		shooters.back().SetWidthHeight(32, 32);
		shooters.back().SetPosition(x, y);
		shooters.back().SetState(STATE_LOOKRIGHT);
	}
	else {
		kamikazes.push_back(Enemy());
		kamikazes.back().SetWidthHeight(32, 32);
		kamikazes.back().SetPosition(x, y);
		kamikazes.back().SetState(STATE_LOOKRIGHT);
	}
}

void Room::addBullet(int x, int y, int d)
{
	bullets.push_back(cShot(x, y));
	bullets.back().SetDirection(d);
	bullets.back().SetState(STATE_SHOTING);
	bullets.back().SetWidthHeight(10, 10);
}


bool Room::boxCollision(int x00, int y00, int x01, int y01, int x10, int y10, int x11, int y11)
{
	if (x11 < x00 || x10 > x01 || y11 < y00 || y10 > y01) return false;
	return true;
}

void Room::processBullet(int i) 
{
	int x, y;
	int w, h;
	
	if(bullets[i].GetState() == STATE_SHOT_END) return; 

	bullets[i].getPosition(&x, &y);
	bullets[i].getDimensions(&h,&w);
	if (collidesMap(x, y)) {
		bullets[i].SetState(STATE_SHOT_END);
		return;
	}
	
	bullets[i].move();
}

bool Room::processEnemy(Enemy& e) 
{
	int x, y;
	int w, h;
	e.GetPosition(&x, &y);
	e.GetWidthHeight(&w,&h);

	for (int i = 0; i < bullets.size(); ++i) {
		if (bullets[i].GetState() == STATE_SHOTING)  {
			int bx, by;
			int bw, bh;
			bullets[i].getPosition(&bx, &by);
			bullets[i].getDimensions(&bw, &bh);
			if (boxCollision(x,y,x+w,y+h,bx,by,bx+bw,by+bh)) {
				bullets[i].SetState(STATE_SHOT_END);
				return false;
			}
		}
	}

	return true;
}

void Room::processShooter(int i, int x1, int y1, int x2, int y2)
{
	if (!shooters[i].isAlive()) return;
	if (!processEnemy(shooters[i])) shooters[i].kill();
}

void Room::processKamikaze(int i, int x1, int y1, int x2, int y2)
{
	if (!kamikazes[i].isAlive()) return;
	if (!processEnemy(kamikazes[i])) kamikazes[i].kill();
}

int Room::process(int x0, int y0, int x1, int y1) 
{
	for (int i = 0; i < bullets.size(); ++i) processBullet(i);
	for (int i = 0; i < shooters.size(); ++i) processShooter(i, x1, y1, x0, y0);
	for (int i = 0; i < kamikazes.size(); ++i) processKamikaze(i, x1, y1, x0, y0);
	return collides(x0, y0, x1, y1);
}

void Room::drawRoom(GLuint texBullets, GLuint texShooter, GLuint texKamikaze) 
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, bgTexId);
	glCallList(bgDisplayList);

	glBindTexture(GL_TEXTURE_2D, fgTexId);
	glCallList(fgDisplayList);

	glDisable(GL_TEXTURE_2D);

	for (int i = 0; i < shooters.size(); ++i) {
		if (shooters[i].isAlive()) shooters[i].Draw(texShooter);
	}
	for (int i = 0; i < kamikazes.size(); ++i) {
		if (kamikazes[i].isAlive()) kamikazes[i].Draw(texKamikaze);
	}
	for (int i = 0; i < bullets.size(); ++i) {
		if (bullets[i].GetState() == STATE_SHOTING) bullets[i].Draw(texBullets);
	}
}

void Room::deleteDisplayLists()
{
	glDeleteLists(bgDisplayList, 1);
	glDeleteLists(fgDisplayList, 1);
}