#include "cShot.h"
#include "cScene.h"


cShot::cShot(int x, int y)
{
	vecDir.x = 3;
	vecDir.y = 0;
	this->x = x;
	this->y = y;
	frame = 0;
}


cShot::~cShot(void)
{
}

void cShot::Draw(int tex_id)
{
	float xo,yo,xf,yf;

	switch(state)
	{
		case STATE_SHOTING:			xo = 0.0f + (frame*1.0f/8.0f); yo = 0.0f;
									break;
	}
	xf = xo + 1.0/8.0f;
	yf = 1;


	int screen_x,screen_y;
	
	x += vecDir.x;
	y += vecDir.y;

	screen_x = x + SCENE_Xo;
	screen_y = y + SCENE_Yo + (BLOCK_SIZE - TILE_SIZE);
	
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		glTexCoord2f(xo,yo);	glVertex2i(screen_x  ,screen_y);
		glTexCoord2f(xf,yo);	glVertex2i(screen_x+w,screen_y);
		glTexCoord2f(xf,yf);	glVertex2i(screen_x+w,screen_y+h);
		glTexCoord2f(xo,yf);	glVertex2i(screen_x  ,screen_y+h);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	++frame;
	if(frame == 8) frame = 0;
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
			vecDir.y = 3;
			break;
		case 1:
			vecDir.x = 2.1;
			vecDir.y = 2.1;
			break;
		case 2:
			vecDir.x = 3;
			vecDir.y = 0;
			break;
		case 3:
			vecDir.x = 2.1;
			vecDir.y = -2.1;
			break;
		case 4:
			vecDir.x = 0;
			vecDir.y = -3;
			break;
		case 5:
			vecDir.x = -2.1;
			vecDir.y = -2.1;
			break;
		case 6:
			vecDir.x = -3;
			vecDir.y = 0;
			break;
		case 7:
			vecDir.x = -2.1;
			vecDir.y = 2.1;
			break;
	}

}