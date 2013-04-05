#pragma once

#include "cBicho.h"
#include "Level.h"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2
#define COOL_DOWN           10

class cPlayer: public cBicho
{
private:
	int coolDown;

	bool Collides(Level& l, int offsetx, int offsety);

public:
	cPlayer();
	~cPlayer();

	void MoveUp(Level& l);
	void MoveUpRight(Level& l);
	void MoveRight(Level& l);
	void MoveDownRight(Level& l);
	void MoveDown(Level& l);
	void MoveDownLeft(Level& l);
	void MoveLeft(Level& l);
	void MoveUpLeft(Level& l);

	void Draw(int tex_id);

	bool shoot();
};
