#include "cGame.h"
#include "Globals.h"
#include <iostream>
#include <ctime>


cGame::cGame(void)
{
}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
	srand(time(0));
	repressed = true;

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	return Scene.initScene();
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
			specialkeys[GLUT_KEY_UP] *= 3;
			specialkeys[GLUT_KEY_DOWN] *= 3;
			specialkeys[GLUT_KEY_LEFT] *= 3;
			specialkeys[GLUT_KEY_RIGHT] *= 3;
		}
	}
	else {
		keys[key] = press;
		if(key == 'p') repressed = true;
		if (!press) {
			keys[GLUT_KEY_UP] *= 3;
			keys[GLUT_KEY_DOWN] *= 3;
			keys[GLUT_KEY_LEFT] *= 3;
			keys[GLUT_KEY_RIGHT] *= 3;
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

	/*
	if(keys['p'] && repressed) {
		if(secondPlayer) secondPlayer = false;
		else {
			int auxx, auxy;
			Player.GetPosition(&auxx, &auxy);
			Player2.SetPosition(auxx + 4, auxy);
			secondPlayer = true;
		}
		repressed = false;
	}
	*/

	if(specialkeys[GLUT_KEY_UP] && specialkeys[GLUT_KEY_LEFT]) {
		Scene.movePlayer(0, cScene::UPL);
	}
	else if(specialkeys[GLUT_KEY_UP] && specialkeys[GLUT_KEY_RIGHT]) {
		Scene.movePlayer(0, cScene::UPR);
	}
	else if(specialkeys[GLUT_KEY_UP]) {
		if (specialkeys[GLUT_KEY_UP] > 1) --specialkeys[GLUT_KEY_UP];
		else Scene.movePlayer(0, cScene::UP);
	}
	else if(specialkeys[GLUT_KEY_DOWN] && specialkeys[GLUT_KEY_LEFT]) {
		Scene.movePlayer(0, cScene::DOWNL);
	}
	else if(specialkeys[GLUT_KEY_DOWN] && specialkeys[GLUT_KEY_RIGHT]) {
		Scene.movePlayer(0, cScene::DOWNR);
	}
	else if(specialkeys[GLUT_KEY_DOWN]) {
		if (specialkeys[GLUT_KEY_DOWN] > 1) --specialkeys[GLUT_KEY_DOWN];
		else Scene.movePlayer(0, cScene::DOWN);
	}
	else if(specialkeys[GLUT_KEY_LEFT])	{
		if (specialkeys[GLUT_KEY_LEFT] > 1) --specialkeys[GLUT_KEY_LEFT];
		else Scene.movePlayer(0, cScene::LEFT);
	}
	else if(specialkeys[GLUT_KEY_RIGHT]) {
		if (specialkeys[GLUT_KEY_RIGHT] > 1) --specialkeys[GLUT_KEY_RIGHT];
		else Scene.movePlayer(0, cScene::RIGHT);
	}
	else Scene.movePlayer(0, cScene::STOP);
	
	if(keys['-']) Scene.movePlayer(0, cScene::SHOT);

	//Player 2
	if(true){
		if(keys['w'] && keys['a']) {
			Scene.movePlayer(1, cScene::UPL);
		}
		else if(keys['w'] && keys['d']) {
			Scene.movePlayer(1, cScene::UPR);
		}
		else if(keys['w']) {
			if (keys['w'] > 1) --keys['w'];
			else Scene.movePlayer(1, cScene::UP);
		}
		else if(keys['s'] && keys['a']) {
			Scene.movePlayer(1, cScene::DOWNL);
		}
		else if(keys['s'] && keys['d']) {
			Scene.movePlayer(1, cScene::DOWNR);
		}
		else if(keys['s']) {
			if (keys['s'] > 1) --keys['s'];
			else Scene.movePlayer(1, cScene::DOWN);
		}
		else if(keys['a'])			{
			if (keys['a'] > 1) --keys['a'];
			else Scene.movePlayer(1, cScene::LEFT);
		}
		else if(keys['d'])	{
			if (keys['d'] > 1) --keys['d'];
			else Scene.movePlayer(1, cScene::RIGHT);
		}
		else Scene.movePlayer(1, cScene::STOP);

		if (keys[' ']) Scene.movePlayer(1, cScene::SHOT);
	}

	return Scene.process(AI);
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	Scene.Draw(GAME_HEIGHT);

	glutSwapBuffers();
}
