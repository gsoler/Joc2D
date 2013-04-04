#include "cScene.h"
#include "Globals.h"

cScene::cScene(void)
{
}

cScene::~cScene(void)
{
	for (int i = 0; i < nivells.size(); ++i) nivells[i].deleteLevel();
}

void cScene::LoadLevel(cData &data, int n)
{
	Level l;
	l.addRoom(TILE_SIZE*10,TILE_SIZE*11,32,TILE_SIZE, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);
	l.addRoom(TILE_SIZE*11,TILE_SIZE*11,32,TILE_SIZE, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::MAZE);
	nivells.push_back(l);
}

void cScene::Draw(int level)
{
	nivells[level].drawLevel();
}

Level* cScene::GetLevel(int level)
{
	return &nivells[level];
}