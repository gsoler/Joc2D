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
	l.addRoom(832,640,16,64, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);
	l.addRoom(840,640,16,64, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::MAZE);
	l.addRoom(832,640,20,70, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);
	l.addRoom(600,700,20,70, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);
	l.addRoom(600,700,20,70, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);

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