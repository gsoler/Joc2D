#pragma once

#define STATE_SHOT_END 0
#define STATE_SHOTING 1

class cShot
{
public:
	cShot(void);
	~cShot(void);
	void Draw();
	void SetWidthHeight(int width, int height);
	void SetState(int state);

private:
	int x,y;
	int w,h;
	int state;
	int dx,dy;
};

