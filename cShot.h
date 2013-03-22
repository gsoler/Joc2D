#pragma once

#include "cBicho.h"

#define STATE_SHOT_END 0
#define STATE_SHOTING 1

class cShot : public cBicho
{
public:
	cShot(int x, int y);
	~cShot(void);
	void Draw(int tex_id);
	void SetWidthHeight(int width, int height);
	void SetState(int state);
	int GetState();
	void SetDirection(int Direction);

private:
	int x,y;
	int w,h;
	int state;

	struct {
		float x;
		float y;
	} vecDir;
};

