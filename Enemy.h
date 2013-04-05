#pragma once

#include "cBicho.h"


class Enemy : public cBicho
{
public:
	Enemy(void);
	~Enemy(void);

	void Draw(int tex_id);

private:
	int state;
};