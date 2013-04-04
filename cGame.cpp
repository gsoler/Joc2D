#include "cGame.h"
#include "Globals.h"
#include <iostream>
#include <ctime>


cGame::cGame(void)
{
	PosPant = 0;
	level = 0;
}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
	srand(time(0));

	bool res=true;
	nextShot1 = 0;
	nextShot2 = 0;
	repressed = true;

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization
	res = Data.LoadImage(IMG_BLOCKS,"textures.png",GL_RGBA);
	if(!res) return false;
	
	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"player2.png",GL_RGBA);
	if(!res) return false;
	Player.SetWidthHeight(32,32);
	Player.SetTile(4,1);
	Player.SetState(STATE_LOOKRIGHT);

	//Player2 initialization
	res = Data.LoadImage(IMG_PLAYER2,"player3.png",GL_RGBA);
	if(!res) return false;
	Player2.SetWidthHeight(32,32);
	Player2.SetTile(5,1);
	Player2.SetState(STATE_LOOKRIGHT);
	secondPlayer = true;

	//Shot initialization
	res = Data.LoadImage(IMG_SHOT,"shot.png",GL_RGBA);
	if(!res) return false;

	//Enemies initialization
	res = Data.LoadImage(IMG_ENEMY1,"enemy1.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_ENEMY2,"enemy2.png",GL_RGBA);
	if(!res) return false;

	Scene.LoadLevel(Data, 1);

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
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press, bool special)
{
	if(special) {
		specialkeys[key] = press;
		if (!press) {
			specialkeys[GLUT_KEY_UP]*= 3;
			specialkeys[GLUT_KEY_DOWN]*= 3;
			specialkeys[GLUT_KEY_LEFT]*= 3;
			specialkeys[GLUT_KEY_RIGHT]*= 3;
		}
	}
	else {
		keys[key] = press;
		if(key == 'p') repressed = true;
		if (!press) {
			keys[GLUT_KEY_UP]*= 3;
			keys[GLUT_KEY_DOWN]*= 3;
			keys[GLUT_KEY_LEFT]*= 3;
			keys[GLUT_KEY_RIGHT]*= 3;
		}
	}
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

	if(keys['p'] && repressed) {
		if(secondPlayer) secondPlayer = false;
		else secondPlayer = true;
		repressed = false;
	}
	
	if(specialkeys[GLUT_KEY_UP] && specialkeys[GLUT_KEY_LEFT]) {
		Player.MoveUpLeft(Scene.GetLevel(level));
	}
	else if(specialkeys[GLUT_KEY_UP] && specialkeys[GLUT_KEY_RIGHT]) {
		Player.MoveUpRight(Scene.GetLevel(level));
	}
	else if(specialkeys[GLUT_KEY_UP]) {
		if (specialkeys[GLUT_KEY_UP] > 1) --specialkeys[GLUT_KEY_UP];
		else Player.MoveUp(Scene.GetLevel(level));
	}
	else if(specialkeys[GLUT_KEY_DOWN] && specialkeys[GLUT_KEY_LEFT]) {
		Player.MoveDownLeft(Scene.GetLevel(level));
	}
	else if(specialkeys[GLUT_KEY_DOWN] && specialkeys[GLUT_KEY_RIGHT]) {
		Player.MoveDownRight(Scene.GetLevel(level));
	}
	else if(specialkeys[GLUT_KEY_DOWN]) {
		if (specialkeys[GLUT_KEY_DOWN] > 1) --specialkeys[GLUT_KEY_DOWN];
		else Player.MoveDown(Scene.GetLevel(level));
	}
	else if(specialkeys[GLUT_KEY_LEFT])			{
		
		if (specialkeys[GLUT_KEY_LEFT] > 1) --specialkeys[GLUT_KEY_LEFT];
		else Player.MoveLeft(Scene.GetLevel(level));
	}
	else if(specialkeys[GLUT_KEY_RIGHT])	{
		if (specialkeys[GLUT_KEY_RIGHT] > 1) --specialkeys[GLUT_KEY_RIGHT];
		else Player.MoveRight(Scene.GetLevel(level));
	}
	else Player.Stop();
	
	//Player 2
	if(keys['w'] && keys['a']) {
		Player2.MoveUpLeft(Scene.GetLevel(level));
	}
	else if(keys['w'] && keys['d']) {
		Player2.MoveUpRight(Scene.GetLevel(level));
	}
	else if(keys['w']) {
		if (keys['w'] > 1) --keys['w'];
		else Player2.MoveUp(Scene.GetLevel(level));
	}
	else if(keys['s'] && keys['a']) {
		Player2.MoveDownLeft(Scene.GetLevel(level));
	}
	else if(keys['s'] && keys['d']) {
		Player2.MoveDownRight(Scene.GetLevel(level));
	}
	else if(keys['s']) {
		if (keys['s'] > 1) --keys['s'];
		else Player2.MoveDown(Scene.GetLevel(level));
	}
	else if(keys['a'])			{
		if (keys['a'] > 1) --keys['a'];
		else Player2.MoveLeft(Scene.GetLevel(level));
	}
	else if(keys['d'])	{
		if (keys['d'] > 1) --keys['d'];
		else Player2.MoveRight(Scene.GetLevel(level));
	}
	else Player2.Stop();
	
	int t1, t2;

	
	if(keys['-'])					{
		
		if(nextShot1 <= 0){
			int x, y;
			Player.GetPosition(&x,&y);
			cShot Shot = cShot(x + TILE_SIZE/2, y + TILE_SIZE/2); //Inicialitzem el shot a la posicio del jugador, en el centre d l'sprite
			Shot.SetWidthHeight(10,10);
			Shot.SetState(STATE_SHOTING);
			Shot.SetDirection(Player.GetState());
			Shots.push_back(Shot);
			nextShot1 = 10;
		}
		else --nextShot1;

	}
	if(keys[' '])					{
		
		if(nextShot2 <= 0){
			int x, y;
			Player2.GetPosition(&x,&y);
			cShot Shot = cShot(x + TILE_SIZE/2, y + TILE_SIZE/2); //Inicialitzem el shot a la posicio del jugador, en el centre d l'sprite
			Shot.SetWidthHeight(7,7);
			Shot.SetState(STATE_SHOTING);
			Shot.SetDirection(Player2.GetState());
			Shots2.push_back(Shot);
			nextShot2 = 10;
		}
		else --nextShot2;

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
	y = PosicioMinima();
	glLoadIdentity();

	std::cout << y << std::endl;
	if(y > PosPant + GAME_HEIGHT/2 - 50)
		PosPant += STEP_LENGTH;

	else if(y < PosPant + GAME_HEIGHT/8 - 50)
		PosPant -= STEP_LENGTH;

	
	glTranslatef(0.0f, -PosPant*1.0f, 0.0f);
	
	Scene.Draw(0);
	Player.Draw(Data.GetID(IMG_PLAYER));

	if(secondPlayer) Player2.Draw(Data.GetID(IMG_PLAYER2));

	auxShots = Shots;
	Shots.clear();
	
	for(unsigned int i = 0; i < auxShots.size(); ++i){
		if(auxShots[i].GetState() == STATE_SHOTING){
			auxShots[i].Draw(IMG_SHOT);
			Shots.push_back(auxShots[i]);
		}
	}
	auxShots.clear();

	auxShots = Shots2;
	Shots2.clear();
	for (int i = 0; i < auxShots.size(); ++i){
		if (auxShots[i].GetState() == STATE_SHOTING){
			auxShots[i].Draw(IMG_SHOT);
			Shots2.push_back(auxShots[i]);
		}
	}
	auxShots.clear();

	glutSwapBuffers();
}

int cGame::PosicioMinima()
{
	int auxx, auxy, auxx2, auxy2;
	Player.GetPosition(&auxx, &auxy);
	if(secondPlayer) {
		Player2.GetPosition(&auxy2, &auxy2);
		return min(auxy, auxy2);
	}
	return auxy;
}