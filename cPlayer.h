#pragma once

#include "cBicho.h"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2
#define COOL_DOWN           10

class cPlayer: public cBicho
{
private:
	int coolDown;

public:
	cPlayer();
	~cPlayer();

	void Draw(int tex_id);

	bool shoot();
};
