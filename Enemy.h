#pragma once

#include "cBicho.h"
#include <vector>

class Enemy : public cBicho
{
public:
	typedef std::pair<int, int> Vec2;

	Enemy(void);
	~Enemy(void);

	void Draw(int tex_id);
	void parseAI(const std::vector<Vec2>& path);

private:
	int state;
	std::vector<int> commands;

};