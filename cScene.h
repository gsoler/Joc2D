#pragma once

#include "cTexture.h"
#include "Level.h"
#include "cData.h"
#include <vector>

#define SCENE_Xo		(2*TILE_SIZE)
#define SCENE_Yo		TILE_SIZE
#define SCENE_WIDTH		36
#define SCENE_HEIGHT	512

#define FILENAME		"level"
#define FILENAME_EXT	".txt"

#define TILE_SIZE		16
#define BLOCK_SIZE		24

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	void LoadLevel(cData &data);
	void Draw(int level, int bottom, int top);
	Level* GetLevel(int level);

private:
	std::vector<Level> nivells;								//actual level display list
};
