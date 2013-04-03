#include "cScene.h"
#include "Globals.h"
#include "cGame.h"

cScene::cScene(void)
{
}

cScene::~cScene(void)
{
}

void cScene::LoadLevel(cData &data)
{
	Level l;
	l.addRoom(600,600,10,60,data.GetID(IMG_BLOCKS),data.GetID(IMG_BLOCKS), l.FIELD);
	nivells.push_back(l);
}

void cScene::Draw(int level, int bottom, int top)
{
	nivells[level].drawLevel(bottom, top);
}

Level* cScene::GetLevel(int level)
{
	return &nivells[level];
}