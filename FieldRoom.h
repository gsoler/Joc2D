#pragma once

#include "Room.h"

class FieldRoom : public Room
{
private:


public:
	FieldRoom(int heigth, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId);
	~FieldRoom(void);

	void createRoom();
};

