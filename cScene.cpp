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
	l.addRoom(800,800,8,10, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);
	l.addRoom(800,800,8,10, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::MAZE);
	l.addRoom(832,640,8,10, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);
	l.addRoom(600,700,20,10, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);
	l.addRoom(600,700,20,10, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);

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