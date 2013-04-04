#pragma once

#include "cBicho.h"


class Enemy
{
public:
	Enemy(void);
	~Enemy(void);

	void Draw(int tex_id);

private:
	int state;
	cBicho bicho;

};