#include "cGame.h"
#include "Globals.h"
#include <iostream>



cGame::cGame(void)
{
	PosPant = 0;
}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
	bool res=true;

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization
	res = Data.LoadImage(IMG_BLOCKS,"blocks.png",GL_RGBA);
	if(!res) return false;
	res = Scene.LoadLevel(1);
	if(!res) return false;

	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"bub.png",GL_RGBA);
	if(!res) return false;
	Player.SetWidthHeight(32,32);
	Player.SetTile(4,1);
	Player.SetState(STATE_LOOKRIGHT);

	//Player2 initialization
	res = Data.LoadImage(IMG_PLAYER2,"bub.png",GL_RGBA);
	if(!res) return false;
	Player2.SetWidthHeight(32,32);
	Player2.SetTile(10,1);
	Player2.SetState(STATE_LOOKRIGHT);
	secondPlayer = true;

	//Shot initialization
	res = Data.LoadImage(IMG_SHOT,"shot.png",GL_RGBA);
	if(!res) return false;

	return res;
}

bool cGame::Loop()
{
	bool res=true;

	int t1, t2;

	t1 = glutGet(GLUT_ELAPSED_TIME);

	res = Process();
	if(res) Render();

	do { t2 = glutGet(GLUT_ELAPSED_TIME);
	} while (t2 - t1 < 10);

	return res;
}

void cGame::Finalize()
{
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
}

//Process
bool cGame::Process()
{
	bool res=true;
	
	//Process Input
	if(keys[27])	res=false;
	
	if(keys[GLUT_KEY_UP] && keys[GLUT_KEY_LEFT]) {
		Player.MoveUpLeft(Scene.GetMap());
	}
	else if(keys[GLUT_KEY_UP] && keys[GLUT_KEY_RIGHT]) {
		Player.MoveUpRight(Scene.GetMap());
	}
	else if(keys[GLUT_KEY_UP]) {
		Player.MoveUp(Scene.GetMap());
	}
	else if(keys[GLUT_KEY_DOWN] && keys[GLUT_KEY_LEFT]) {
		Player.MoveDownLeft(Scene.GetMap());
	}
	else if(keys[GLUT_KEY_DOWN] && keys[GLUT_KEY_RIGHT]) {
		Player.MoveDownRight(Scene.GetMap());
	}
	else if(keys[GLUT_KEY_DOWN]) {
		Player.MoveDown(Scene.GetMap());
	}
	if(keys[GLUT_KEY_LEFT])			{
		Player.MoveLeft(Scene.GetMap());
	}
	else if(keys[GLUT_KEY_RIGHT])	{
		Player.MoveRight(Scene.GetMap());
	}
	else Player.Stop();
	
	//Player 2
	if(keys['w'] && keys['a']) {
		Player2.MoveUpLeft(Scene.GetMap());
	}
	else if(keys['w'] && keys['d']) {
		Player2.MoveUpRight(Scene.GetMap());
	}
	else if(keys['w']) {
		Player2.MoveUp(Scene.GetMap());
	}
	else if(keys['s'] && keys['a']) {
		Player2.MoveDownLeft(Scene.GetMap());
	}
	else if(keys['s'] && keys['d']) {
		Player2.MoveDownRight(Scene.GetMap());
	}
	else if(keys['s']) {
		Player2.MoveDown(Scene.GetMap());
	}
	if(keys['a'])			{
		Player2.MoveLeft(Scene.GetMap());
	}
	else if(keys['d'])	{
		Player2.MoveRight(Scene.GetMap());
	}
	else Player2.Stop();
	
	int t1, t2;

	
	if(keys[' '])					{
		
		int x, y;
		Player.GetPosition(&x,&y);
		cShot Shot = cShot(x + TILE_SIZE/2, y + TILE_SIZE/2); //Inicialitzem el shot a la posicio del jugador, en el centre d l'sprite
		Shot.SetWidthHeight(7,7);
		Shot.SetState(STATE_SHOTING);
		Shot.SetDirection(Player.GetState());
		Shots.push_back(Shot);

	}
	if(keys[GLUT_ACTIVE_CTRL])					{
		
		int x, y;
		Player2.GetPosition(&x,&y);
		cShot Shot = cShot(x + TILE_SIZE/2, y + TILE_SIZE/2); //Inicialitzem el shot a la posicio del jugador, en el centre d l'sprite
		Shot.SetWidthHeight(7,7);
		Shot.SetState(STATE_SHOTING);
		Shot.SetDirection(Player2.GetState());
		Shots2.push_back(Shot);

	}

	
	
	//Game Logic
	//Player.Logic(Scene.GetMap());

	return res;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int x, y;
	Player.GetPosition(&x, &y);

	glLoadIdentity();

	std::cout << y << std::endl;
	if(y > PosPant + GAME_HEIGHT/2 - 50)
		PosPant += STEP_LENGTH;

	else if(y < PosPant + GAME_HEIGHT/8 - 50)
		PosPant -= STEP_LENGTH;

	glTranslatef(0.0f, -PosPant*1.0f, 0.0f);

	Scene.Draw(Data.GetID(IMG_BLOCKS));
	Player.Draw(Data.GetID(IMG_PLAYER));
	if(secondPlayer)
		Player2.Draw(Data.GetID(IMG_PLAYER2));
	auxShots = Shots;
	Shots.clear();
	for(int i = 0; i < auxShots.size(); ++i){
		if(auxShots[i].GetState() == STATE_SHOTING){
			auxShots[i].Draw(IMG_SHOT);
			Shots.push_back(auxShots[i]);
		}
	}
	auxShots.clear();

	auxShots = Shots2;
	Shots2.clear();
	for(int i = 0; i < auxShots.size(); ++i){
		if(auxShots[i].GetState() == STATE_SHOTING){
			auxShots[i].Draw(IMG_SHOT);
			Shots2.push_back(auxShots[i]);
		}
	}
	auxShots.clear();

	glutSwapBuffers();
}
