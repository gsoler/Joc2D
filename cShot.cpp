#include "cShot.h"
#include "cScene.h"


cShot::cShot(int x, int y)
{
	vecDir.x = 1;
	vecDir.y = 0;
	this->x = x;
	this->y = y;
}


cShot::~cShot(void)
{
}

void cShot::Draw(int tex_id)
{
	int screen_x,screen_y;
	
	x += vecDir.x;
	y += vecDir.y;

	screen_x = x + SCENE_Xo;
	screen_y = y + SCENE_Yo + (BLOCK_SIZE - TILE_SIZE);

	int x0 = 0, y0 = 0;

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		glTexCoord2f(x0,y0);		glVertex2i(screen_x  ,screen_y);
		glTexCoord2f(x0+0.2,y0);	glVertex2i(screen_x+w,screen_y);
		glTexCoord2f(x0+0.2,y0+0.2);	glVertex2i(screen_x+w,screen_y+h);
		glTexCoord2f(x0,y0+0.2);	glVertex2i(screen_x  ,screen_y+h);
	glEnd();
}

void cShot::SetWidthHeight(int width, int height)
{
	w = width;
	h = height;
}

void cShot::SetState(int state)
{
	this->state = state;
}

int cShot::GetState() {
	return state;
}

void cShot::SetDirection(int dir)
{
	switch (dir%8) {
		case 0:
			vecDir.x = 0;
			vecDir.y = 1;
			break;
		case 1:
			vecDir.x = 0.7;
			vecDir.y = 0.7;
			break;
		case 2:
			vecDir.x = 1;
			vecDir.y = 0;
			break;
		case 3:
			vecDir.x = 0.7;
			vecDir.y = -0.7;
			break;
		case 4:
			vecDir.x = 0;
			vecDir.y = -1;
			break;
		case 5:
			vecDir.x = -0.7;
			vecDir.y = -0.7;
			break;
		case 6:
			vecDir.x = -1;
			vecDir.y = 0;
			break;
		case 7:
			vecDir.x = -0.7;
			vecDir.y = 0.7;
			break;
	}

}