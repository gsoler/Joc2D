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
	l.addRoom(600,600,10,60, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);
	l.addRoom(600,600,10,60, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);
	l.addRoom(600,600,10,60, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);
	l.addRoom(600,600,10,60, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);
	l.addRoom(600,600,10,60, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);

	nivells.push_back(l);

}

void cScene::Draw(int level, int bottom, int top)
{
	nivells[level].drawLevel(650, 1300);
}

Level* cScene::GetLevel(int level)
{
	return &nivells[level];
}