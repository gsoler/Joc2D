
#include "cScene.h"
#include "Globals.h"

cScene::cScene(void)
{
	currentLevel = 0;
	T = 0;
}

cScene::~cScene(void)
{
	nivells[0].deleteLevel();
	nivells[1].deleteLevel();
}

bool cScene::initScene()
{
	//Scene initialization

	bool res=true;

	res = data.LoadImage(IMG_BLOCKS,"textures.png",GL_RGBA);
	if(!res) return false;
	
	//Player initialization
	res = data.LoadImage(IMG_PLAYER,"player2.png",GL_RGBA);
	if(!res) return false;
	players[0].SetWidthHeight(32,32);
	players[0].SetTile(4,1);
	players[0].SetState(STATE_LOOKRIGHT);

	//Player2 initialization
	res = data.LoadImage(IMG_PLAYER2,"player3.png",GL_RGBA);
	if(!res) return false;
	players[1].SetWidthHeight(32,32);
	players[1].SetTile(5,1);
	players[1].SetState(STATE_LOOKRIGHT);
	//secondPlayer = true;

	//Shot initialization
	res = data.LoadImage(IMG_SHOT,"shot.png",GL_RGBA);
	if(!res) return false;

	//Enemies initialization
	res = data.LoadImage(IMG_ENEMY1,"enemy1.png",GL_RGBA);
	if(!res) return false;
	res = data.LoadImage(IMG_ENEMY2,"enemy2.png",GL_RGBA);
	if(!res) return false;

	LoadLevels();
}

void cScene::LoadLevels()
{
	
	nivells[0].addRoom(TILE_SIZE*11,TILE_SIZE*11,32,TILE_SIZE, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);
	nivells[0].addRoom(TILE_SIZE*11,TILE_SIZE*11,32,TILE_SIZE, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::MAZE);
	nivells[0].addRoom(TILE_SIZE*11,TILE_SIZE*11,32,TILE_SIZE, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);
	nivells[0].addRoom(TILE_SIZE*11,TILE_SIZE*11,32,TILE_SIZE, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::MAZE);
	nivells[0].addRoom(TILE_SIZE*11,TILE_SIZE*11,32,TILE_SIZE, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);

	nivells[1].addRoom(TILE_SIZE*11,TILE_SIZE*11,32,TILE_SIZE, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);
	nivells[1].addRoom(TILE_SIZE*11,TILE_SIZE*11,32,TILE_SIZE, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);
	nivells[1].addRoom(TILE_SIZE*11,TILE_SIZE*11,32,TILE_SIZE, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);
	nivells[1].addRoom(TILE_SIZE*11,TILE_SIZE*11,32,TILE_SIZE, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::MAZE);
	nivells[1].addRoom(TILE_SIZE*11,TILE_SIZE*11,32,TILE_SIZE, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::MAZE);
	nivells[1].addRoom(TILE_SIZE*11,TILE_SIZE*11,32,TILE_SIZE, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::MAZE);
	nivells[1].addRoom(TILE_SIZE*11,TILE_SIZE*11,32,TILE_SIZE, data.GetID(IMG_BLOCKS), data.GetID(IMG_BLOCKS), Level::FIELD);
}

void cScene::movePlayer(int p, MoveType m) 
{
	if (p >= 2) return;

	switch (m) {
		case UP: players[p].MoveUp(nivells[currentLevel]);
			break;
		case DOWN: players[p].MoveDown(nivells[currentLevel]);
			break;
		case LEFT: players[p].MoveLeft(nivells[currentLevel]);
			break;
		case RIGHT: players[p].MoveRight(nivells[currentLevel]);
			break;
		case UPL: players[p].MoveUpLeft(nivells[currentLevel]);
			break;
		case UPR: players[p].MoveUpRight(nivells[currentLevel]);
			break;
		case DOWNL: players[p].MoveDownLeft(nivells[currentLevel]);
			break;
		case DOWNR: players[p].MoveDownRight(nivells[currentLevel]);
			break;
		case STOP: players[p].Stop();
			break;
		case SHOT: addShot(p);
		default:
			break;
	}
}

void cScene::addShot(int p)
{
	if (players[p].shoot()) {
		int x;
		int y;

		players[p].GetPosition(&x, &y);
		int d = players[p].GetState();
		nivells[currentLevel].addBullet(x, y, d);
	}
}

bool cScene::process()
{
	int x0; 
	int y0;
	int x1;
	int y1;

	players[0].GetPosition(&x0, &y0);
	players[1].GetPosition(&x1, &y1);
	nivells[currentLevel].proccess(x0, y0, x1, y1);
	return true;
}

void cScene::Draw(int h)
{
	int x0; 
	int y0;
	int x1;
	int y1;

	players[0].GetPosition(&x0, &y0);
	players[1].GetPosition(&x1, &y1);
	int y = min (y0, y1);

	if (y > T + h/2 - 50) T += STEP_LENGTH;
	else if (y < T + h/8 - 50) T -= STEP_LENGTH;

	glTranslatef(0.0f, -T*1.0f, 0.0f);

	nivells[currentLevel].drawLevel();
	
	players[0].Draw(data.GetID(IMG_PLAYER));
	players[1].Draw(data.GetID(IMG_PLAYER2));
}

