#pragma once

#define STATE_SHOT_END 0
#define STATE_SHOTING 1

class cShot
{
public:
	cShot(int x, int y);
	~cShot(void);
	void Draw(int tex_id);
	void SetWidthHeight(int width, int height);
	void SetState(int state);
	int GetState();
	void getPosition(int* x, int* y);
	void getDimensions(int* h, int* w);
	void SetDirection(int Direction);
	void move();

private:
	float x,y;
	int w,h;
	int state;
	int frame;

	struct {
		float x;
		float y;
	} vecDir;
};

