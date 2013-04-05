#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "Level.h"

#define FRAME_DELAY		8
#define STEP_LENGTH		2
#define JUMP_HEIGHT		96
#define JUMP_STEP		4

#define STATE_LOOKUP		0
#define STATE_LOOKUPRIGHT	1
#define STATE_LOOKRIGHT		2
#define STATE_LOOKDOWNRIGHT	3
#define STATE_LOOKDOWN		4
#define STATE_LOOKDOWNLEFT	5
#define STATE_LOOKLEFT		6
#define STATE_LOOKUPLEFT	7
#define STATE_WALKUP		8
#define STATE_WALKUPRIGHT	9
#define STATE_WALKRIGHT		10
#define STATE_WALKDOWNRIGHT	11
#define STATE_WALKDOWN		12
#define STATE_WALKDOWNLEFT	13
#define STATE_WALKLEFT		14
#define STATE_WALKUPLEFT	15

class cRect
{
public:
	int left,top,
		right,bottom;
};

class cBicho
{
public:

	cBicho(void);
	cBicho(int x,int y,int w,int h);
	~cBicho(void);

	void SetPosition(int x,int y);
	void GetPosition(int *x,int *y);
	void SetTile(int tx,int ty);
	void GetTile(int *tx,int *ty);
	void SetWidthHeight(int w,int h);
	void GetWidthHeight(int *w,int *h);

	bool Collides(Level& l);
	void GetArea(cRect *rc);
	void DrawRect(int tex_id,float xo,float yo,float xf,float yf);
	
	void MoveUp(Level& l);
	void MoveUpRight(Level& l);
	void MoveRight(Level& l);
	void MoveDownRight(Level& l);
	void MoveDown(Level& l);
	void MoveDownLeft(Level& l);
	void MoveLeft(Level& l);
	void MoveUpLeft(Level& l);
	void Stop();

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();
	
private:

	int x,y;
	int w,h;
	int state;

	//bool jumping;
	int jump_alfa;
	int jump_y;

	int seq,delay;
};
