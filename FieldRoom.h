#pragma once

#include "Room.h"

class FieldRoom : public Room
{
private:

	GLuint createBackground(unsigned int seed);
	GLuint createForeground(unsigned int seed);

public:
	FieldRoom(int heigth, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId);
	~FieldRoom(void);

	void createRoom();
};

