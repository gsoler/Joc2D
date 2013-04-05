#pragma once

#include "cScene.h"
#include "AIEngine.h"
#include "MenuPpal.h"

#define GAME_WIDTH	640+64
#define GAME_HEIGHT 480

class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	bool Loop();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press, bool special);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	//Output
	void Render();
	void setMenu(bool estat);

private:
	bool menuact;
	bool repressed;

	unsigned char keys[256];
	unsigned char specialkeys[256];
	
	MenuPpal menu;
	cScene Scene;
	AIEngine AI;
};
