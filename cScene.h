#pragma once

#include "cTexture.h"
#include "Level.h"
#include "cPlayer.h"
#include "cData.h"
#include "AIEngine.h"

#define SCENE_Xo		0
#define SCENE_Yo		0
#define SCENE_WIDTH		36
#define SCENE_HEIGHT	512

#define FILENAME		"level"
#define FILENAME_EXT	".txt"

#define TILE_SIZE		64
#define BLOCK_SIZE		64

class cScene
{
public:
	static const enum MoveType{UP, DOWN, RIGHT, LEFT, UPR, DOWNL, UPL, DOWNR, STOP, SHOT};

	cScene(void);
	virtual ~cScene(void);

	bool initScene();

	bool process(AIEngine& AI);

	void Draw(int h);

	void movePlayer(int p, MoveType m);
	
private:
	cPlayer players[2];
	Level nivells[2];

	float T;
	int currentLevel;

	void LoadLevels();
	void addShot(int p);

	cData data;
};
