#pragma once

#include "cTexture.h"
#include "Level.h"
#include "cData.h"
#include <vector>

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
	cScene(void);
	virtual ~cScene(void);

	void LoadLevel(cData &data, int n);
	void Draw(int level);
	Level* GetLevel(int level);

private:
	std::vector<Level> nivells;	
};
