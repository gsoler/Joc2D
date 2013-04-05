
#include "cPlayer.h"

cPlayer::cPlayer() {}
cPlayer::~cPlayer(){}

void cPlayer::Draw(int tex_id)
{	
	float xo,yo,xf,yf;

	switch(GetState())
	{
		//1
		case STATE_LOOKUP:			xo = 1.0f/6.0f;	yo = 4.0f/8.0f;
									break;
		//4
		case STATE_LOOKUPRIGHT:		xo = 1.0f/6.0f;	yo = 0.0f/8.0f;
									break;
		//1	
		case STATE_LOOKRIGHT:		xo = 1.0f/6.0f;	yo = 3.0f/8.0f;
									break;
		//4
		case STATE_LOOKDOWNRIGHT:	xo = 1.0f/6.0f;	yo = 6.0f/8.0f;
									break;
		//1
		case STATE_LOOKDOWN:		xo = 1.0f/6.0f;	yo = 1.0f/8.0f;
									break;
		//4
		case STATE_LOOKDOWNLEFT:	xo = 1.0f/6.0f;	yo = 5.0f/8.0f;
									break;
		//1
		case STATE_LOOKLEFT:		xo = 1.0f/6.0f;	yo = 2.0f/8.0f;
									break;
		//4
		case STATE_LOOKUPLEFT:		xo = 1.0f/6.0f;	yo = 7.0f/8.0f;
									break;


		//1..3
		case STATE_WALKUP:			xo = 1.0f/6.0f + (GetFrame()*1.0f/6.0f); yo = 4.0f/8.0f;
									NextFrame(6);
									break;
		//4..6
		case STATE_WALKUPRIGHT:		xo = 1.0f/6.0f + (GetFrame()*1.0f/6.0f); yo = 0.0f/8.0f;
									NextFrame(6);
									break;
		//1..3
		case STATE_WALKRIGHT:		xo = 1.0f/6.0f + (GetFrame()*1.0f/6.0f); yo = 3.0f/8.0f;
									NextFrame(6);
									break;
		//4..6
		case STATE_WALKDOWNRIGHT:	xo = 1.0f/6.0f + (GetFrame()*1.0f/6.0f); yo = 6.0f/8.0f;
									NextFrame(6);
									break;
		//1..3
		case STATE_WALKDOWN:		xo = 1.0f/6.0f + (GetFrame()*1.0f/6.0f); yo = 1.0f/8.0f;
									NextFrame(6);
									break;
		//4..6
		case STATE_WALKDOWNLEFT:	xo = 1.0f/6.0f + (GetFrame()*1.0f/6.0f); yo = 5.0f/8.0f;
									NextFrame(6);
									break;
		//1..3
		case STATE_WALKLEFT:		xo = 1.0f/6.0f + (GetFrame()*1.0f/6.0f); yo = 2.0f/8.0f;
									NextFrame(6);
									break;
		//4..6
		case STATE_WALKUPLEFT:		xo = 1.0f/6.0f + (GetFrame()*1.0f/6.0f); yo = 7.0f/8.0f;
									NextFrame(6);
									break;
	}
	xf = xo + 1.0f/6.0f;
	yf = yo - 1.0f/8.0f;

	DrawRect(tex_id,xo,yo,xf,yf);
}

bool cPlayer::Collides(Level& l, int offsetx, int offsety)
{
	return l.collidesMap(x+offsetx, y+offsety);
}

bool cPlayer::shoot() 
{
	if (coolDown == 0) {
		coolDown = COOL_DOWN;
		return true;
	}
	else {
		--coolDown;
		return false;
	}
}

void cPlayer::MoveUp(Level& l)
{
	y += STEP_LENGTH;

	if(Collides(l, 0, h)) {
		y -= STEP_LENGTH;
		state = STATE_LOOKUP;
	}
	else {
		y -= STEP_LENGTH;
		
		cBicho::MoveUp();
	}
}

void cPlayer::MoveUpRight(Level& l)
{
	y += STEP_LENGTH/2;
	x += STEP_LENGTH/2;

	if(Collides(l, w, h)) {
		y -= STEP_LENGTH/2;
		x -= STEP_LENGTH/2;

		state = STATE_LOOKUPRIGHT;
	}
	else {
		y -= STEP_LENGTH/2;
		x -= STEP_LENGTH/2;

		cBicho::MoveUpRight();
	}
}

void cPlayer::MoveRight(Level& l)
{
	x += STEP_LENGTH;

	if (Collides(l, w, 0)) {
		x -= STEP_LENGTH;
		
		state = STATE_LOOKRIGHT;
	}
	else {
		x -= STEP_LENGTH;

		cBicho::MoveRight();
	}
}

void cPlayer::MoveDownRight(Level& l)
{
	y -= STEP_LENGTH/2;
	x += STEP_LENGTH/2;

	if(Collides(l, w, 0)) {
		y += STEP_LENGTH/2;
		x -= STEP_LENGTH/2;
		
		state = STATE_LOOKDOWNRIGHT;
	}
	else {
		y += STEP_LENGTH/2;
		x -= STEP_LENGTH/2;
		
		cBicho::MoveDownRight();
	}
}

void cPlayer::MoveDown(Level& l)
{
	y -= STEP_LENGTH;

	if(Collides(l,0,0)) {
		y += STEP_LENGTH;

		state = STATE_LOOKDOWN;
	}
	else {
		y += STEP_LENGTH;

		cBicho::MoveDown();
	}
}

void cPlayer::MoveDownLeft(Level& l)
{
	y -= STEP_LENGTH/2;
	x -= STEP_LENGTH/2;

	if(Collides(l, 0, 0)) {
		y += STEP_LENGTH/2;
		x += STEP_LENGTH/2;

		state = STATE_LOOKDOWNLEFT;
	}
	else {
		y += STEP_LENGTH/2;
		x += STEP_LENGTH/2;

		cBicho::MoveDownLeft();
	}
}

void cPlayer::MoveLeft(Level& l)
{
	x -= STEP_LENGTH;

	if(Collides(l, 0, 0)) {
		x += STEP_LENGTH;

		state = STATE_LOOKLEFT;
	}
	else {
		x += STEP_LENGTH;

		cBicho::MoveLeft();
	}
}

void cPlayer::MoveUpLeft(Level& l)
{
	y += STEP_LENGTH/2;
	x -= STEP_LENGTH/2;

	if(Collides(l, 0, h)) {
		y -= STEP_LENGTH/2;
		x += STEP_LENGTH/2;

		state = STATE_LOOKUPLEFT;
	}
	else {
		y -= STEP_LENGTH/2;
		x += STEP_LENGTH/2;

		cBicho::MoveUpLeft();
	}
}