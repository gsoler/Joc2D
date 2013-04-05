
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
	res = data.LoadImage(IMG_BLOCKS2,"textures23.png",GL_RGBA);
	if(!res) return false;
	res = data.LoadImage(IMG_BLOCKS3,"wall.png",GL_RGBA);
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
	
	nivells[0].addRoom(TILE_SIZE*11,TILE_SIZE*11,16,TILE_SIZE, data.GetID(IMG_BLOCKS3), data.GetID(IMG_BLOCKS), Level::FIELD);
	nivells[0].addRoom(TILE_SIZE*11,TILE_SIZE*11,16,TILE_SIZE, data.GetID(IMG_BLOCKS3), data.GetID(IMG_BLOCKS), Level::MAZE);
	nivells[0].addRoom(TILE_SIZE*11,TILE_SIZE*11,16,TILE_SIZE, data.GetID(IMG_BLOCKS3), data.GetID(IMG_BLOCKS), Level::FIELD);
	nivells[0].addRoom(TILE_SIZE*11,TILE_SIZE*11,16,TILE_SIZE, data.GetID(IMG_BLOCKS3), data.GetID(IMG_BLOCKS), Level::MAZE);
	nivells[0].addRoom(TILE_SIZE*11,TILE_SIZE*11,16,TILE_SIZE, data.GetID(IMG_BLOCKS3), data.GetID(IMG_BLOCKS), Level::FIELD);

	for (int i = TILE_SIZE; i < TILE_SIZE*(11-2)/3; i+=TILE_SIZE/2) 
		nivells[0].addEnemy(i, TILE_SIZE*11*3-300, Room::SHOOTER);
	for (int i = TILE_SIZE*(11-2)/3 + 200; i < TILE_SIZE*11-100; i+=TILE_SIZE/2) 
		nivells[0].addEnemy(i,TILE_SIZE*11*3-300, Room::SHOOTER);
	for (int i = TILE_SIZE; i < TILE_SIZE*(11-1); i+=TILE_SIZE/2) 
		nivells[0].addEnemy(i, TILE_SIZE*11*5-200, Room::KAMIKAZE);

	nivells[1].addRoom(TILE_SIZE*11,TILE_SIZE*11,16,TILE_SIZE, data.GetID(IMG_BLOCKS3), data.GetID(IMG_BLOCKS2), Level::FIELD);
	nivells[1].addRoom(TILE_SIZE*11,TILE_SIZE*11,16,TILE_SIZE, data.GetID(IMG_BLOCKS3), data.GetID(IMG_BLOCKS2), Level::FIELD);
	nivells[1].addRoom(TILE_SIZE*11,TILE_SIZE*11,16,TILE_SIZE, data.GetID(IMG_BLOCKS3), data.GetID(IMG_BLOCKS2), Level::FIELD);
	nivells[1].addRoom(TILE_SIZE*11,TILE_SIZE*11,16,TILE_SIZE, data.GetID(IMG_BLOCKS3), data.GetID(IMG_BLOCKS2), Level::MAZE);
	nivells[1].addRoom(TILE_SIZE*11,TILE_SIZE*11,16,TILE_SIZE, data.GetID(IMG_BLOCKS3), data.GetID(IMG_BLOCKS2), Level::MAZE);
	nivells[1].addRoom(TILE_SIZE*11,TILE_SIZE*11,16,TILE_SIZE, data.GetID(IMG_BLOCKS3), data.GetID(IMG_BLOCKS2), Level::MMAZE);
	nivells[1].addRoom(TILE_SIZE*11,TILE_SIZE*11,16,TILE_SIZE, data.GetID(IMG_BLOCKS3), data.GetID(IMG_BLOCKS2), Level::FIELD);

	for (int i = TILE_SIZE; i < TILE_SIZE*(11-1); i+=TILE_SIZE/2) 
		nivells[0].addEnemy(i, TILE_SIZE*11*3-200, Room::SHOOTER);

	for (int i = TILE_SIZE; i < TILE_SIZE*(11-1); i+=TILE_SIZE/2) 
		nivells[0].addEnemy(i, TILE_SIZE*11*3-300, Room::KAMIKAZE);

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

bool cScene::process(AIEngine& AI)
{
	int x0, y0, x1, y1;
	int w0, h0, w1, h1;

	players[0].GetPosition(&x0, &y0);
	players[0].GetWidthHeight(&w0, &h0);

	players[1].GetPosition(&x1, &y1);
	players[1].GetWidthHeight(&w1, &h1);

	int flag0 = nivells[currentLevel].process(x0, y0, x0+w0, y0+h0);
	int flag1 = nivells[currentLevel].process(x1, y1, x1+w1, y1+h1);
	
	if (flag0 == 1 || flag1 == 1) currentLevel = 1;
	else if (flag0 == 2 && flag1 == 2) return false;
	return true;
}

void cScene::Draw(int h)
{
	int x0, y0, x1, y1;

	players[0].GetPosition(&x0, &y0);
	players[1].GetPosition(&x1, &y1);
	int y = min (y0, y1);

	if (y > T + h/2 - 50) T += STEP_LENGTH;
	else if (y < T + h/8 - 50) T -= STEP_LENGTH;

	glTranslatef(0.0f, -T*1.0f, 0.0f);

	nivells[currentLevel].drawLevel(data.GetID(IMG_SHOT), data.GetID(IMG_ENEMY1), data.GetID(IMG_ENEMY2));
	
	players[0].Draw(data.GetID(IMG_PLAYER));
	players[1].Draw(data.GetID(IMG_PLAYER2));
}

