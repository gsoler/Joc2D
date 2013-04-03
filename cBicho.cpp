#include "cBicho.h"
#include "cScene.h"
#include "Globals.h"

cBicho::cBicho(void)
{
	seq=0;
	delay=0;

//	jumping = false;
}
cBicho::~cBicho(void){}

cBicho::cBicho(int posx,int posy,int width,int height)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
}
void cBicho::SetPosition(int posx,int posy)
{
	x = posx;
	y = posy;
}
void cBicho::GetPosition(int *posx,int *posy)
{
	*posx = x;
	*posy = y;
}
void cBicho::SetTile(int tx,int ty)
{
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}
void cBicho::GetTile(int *tx,int *ty)
{
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}
void cBicho::SetWidthHeight(int width,int height)
{
	w = width;
	h = height;
}
void cBicho::GetWidthHeight(int *width,int *height)
{
	*width = w;
	*height = h;
}
bool cBicho::Collides(Level *l)
{
	return l->collides(x, y, 0, 0);
}

void cBicho::GetArea(cRect *rc)
{
	rc->left   = x;
	rc->right  = x+w;
	rc->bottom = y;
	rc->top    = y+h;
}

void cBicho::DrawRect(int tex_id,float xo,float yo,float xf,float yf)
{
	int screen_x,screen_y;

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
}

void cBicho::MoveUp(Level *l)
{
	y += STEP_LENGTH;

	if(Collides(l)) {
	
		y -= STEP_LENGTH;
		state = STATE_LOOKUP;
	}
	else {
		if(state != STATE_WALKUP)
		{
			state = STATE_WALKUP;
			seq = 0;
			delay = 0;
		}
	}
}

void cBicho::MoveUpRight(Level *l)
{
	y += STEP_LENGTH/2;
	x += STEP_LENGTH/2;

	if(Collides(l)) {
	
		y -= STEP_LENGTH/2;
		x -= STEP_LENGTH/2;
		state = STATE_LOOKUPRIGHT;
	}
	else {
		if(state != STATE_WALKUPRIGHT)
		{
			state = STATE_WALKUPRIGHT;
			seq = 0;
			delay = 0;
		}
	}
}
void cBicho::MoveRight(Level *l)
{
	x += STEP_LENGTH;

	if(Collides(l)) {
	
		x -= STEP_LENGTH;
		state = STATE_LOOKRIGHT;
	}
	else {
		if(state != STATE_WALKRIGHT)
		{
			state = STATE_WALKRIGHT;
			seq = 0;
			delay = 0;
		}
	}
}
void cBicho::MoveDownRight(Level *l)
{
	y -= STEP_LENGTH/2;
	x += STEP_LENGTH/2;

	if(Collides(l)) {
	
		y += STEP_LENGTH/2;
		x -= STEP_LENGTH/2;
		state = STATE_LOOKDOWNRIGHT;
	}
	else {
		if(state != STATE_WALKDOWNRIGHT)
		{
			state = STATE_WALKDOWNRIGHT;
			seq = 0;
			delay = 0;
		}
	}
}
void cBicho::MoveDown(Level *l)
{
	y -= STEP_LENGTH;

	if(Collides(l)) {
	
		y += STEP_LENGTH;
		state = STATE_LOOKDOWN;
	}
	else {
		if(state != STATE_WALKDOWN)
		{
			state = STATE_WALKDOWN;
			seq = 0;
			delay = 0;
		}
	}
}
void cBicho::MoveDownLeft(Level *l)
{
	y -= STEP_LENGTH/2;
	x -= STEP_LENGTH/2;

	if(Collides(l)) {
	
		y += STEP_LENGTH/2;
		x += STEP_LENGTH/2;
		state = STATE_LOOKDOWNLEFT;
	}
	else {
		if(state != STATE_WALKDOWNLEFT)
		{
			state = STATE_WALKDOWNLEFT;
			seq = 0;
			delay = 0;
		}
	}
}
void cBicho::MoveLeft(Level *l)
{
	x -= STEP_LENGTH;

	if(Collides(l)) {
	
		x += STEP_LENGTH;
		state = STATE_LOOKLEFT;
	}
	else {
		if(state != STATE_WALKLEFT)
		{
			state = STATE_WALKLEFT;
			seq = 0;
			delay = 0;
		}
	}
}
void cBicho::MoveUpLeft(Level *l)
{
	y += STEP_LENGTH/2;
	x -= STEP_LENGTH/2;

	if(Collides(l)) {
	
		y -= STEP_LENGTH/2;
		x += STEP_LENGTH/2;
		state = STATE_LOOKUPLEFT;
	}
	else {
		if(state != STATE_WALKUPLEFT)
		{
			state = STATE_WALKUPLEFT;
			seq = 0;
			delay = 0;
		}
	}
}
void cBicho::Stop()
{
	switch(state)
	{
		case STATE_WALKUP:			state = STATE_LOOKUP;			break;
		case STATE_WALKUPRIGHT:		state = STATE_LOOKUPRIGHT;		break;
		case STATE_WALKRIGHT:		state = STATE_LOOKRIGHT;		break;
		case STATE_WALKDOWNRIGHT:	state = STATE_LOOKDOWNRIGHT;	break;
		case STATE_WALKDOWN:		state = STATE_LOOKDOWN;			break;
		case STATE_WALKDOWNLEFT:	state = STATE_LOOKDOWNLEFT;		break;
		case STATE_WALKLEFT:		state = STATE_LOOKLEFT;			break;
		case STATE_WALKUPLEFT:		state = STATE_LOOKUPLEFT;		break;
	}
}
/*void cBicho::Jump(int *map)
{
	if(!jumping)
	{
		if(CollidesMapFloor(map))
		{
			jumping = true;
			jump_alfa = 0;
			jump_y = y;
		}
	}
}
void cBicho::Logic(int *map)
{
	float alfa;

	if(jumping)
	{
		jump_alfa += JUMP_STEP;
		
		if(jump_alfa == 180)
		{
			jumping = false;
			y = jump_y;
		}
		else
		{
			alfa = ((float)jump_alfa) * 0.017453f;
			y = jump_y + (int)( ((float)JUMP_HEIGHT) * sin(alfa) );
		
			if(jump_alfa > 90)
			{
				//Over floor?
				jumping = !CollidesMapFloor(map);
			}
		}
	}
	else
	{
		//Over floor?
		if(!CollidesMapFloor(map))
			y -= (2*STEP_LENGTH);
	}
}*/
void cBicho::NextFrame(int max)
{
	delay++;
	if(delay == FRAME_DELAY)
	{
		seq++;
		seq%=max;
		delay = 0;
	}
}
int cBicho::GetFrame()
{
	return seq;
}
int cBicho::GetState()
{
	return state;
}
void cBicho::SetState(int s)
{
	state = s;
}