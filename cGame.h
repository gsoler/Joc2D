#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "cData.h"
#include "cBicho.h"
#include "cShot.h"
#include <vector>
using namespace std;

#define GAME_WIDTH	640
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
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	//Output
	void Render();

private:
	int PosPant;
	unsigned char keys[256];
	cScene Scene;
	cPlayer Player;
	vector<cShot> Shots;
	cData Data;
};