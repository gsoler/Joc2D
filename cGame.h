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
	void ReadKeyboard(unsigned char key, int x, int y, bool press, bool special);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	//Output
	void Render();

private:
	int PosicioMinima();

	int level;
	bool secondPlayer;
	int PosPant;
	int Direction;
	unsigned char keys[256];
	unsigned char specialkeys[256];
	cScene Scene;
	cPlayer Player;
	cPlayer Player2;
	vector<cShot> Shots;
	vector<cShot> Shots2;
	vector<cShot> auxShots;
	cData Data;
};
