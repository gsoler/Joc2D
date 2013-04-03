#pragma once

#include "Room.h"

class FieldRoom : public Room
{
private:

	void createBackground(void);
	void createForeground(void);

public:
	FieldRoom(int heigth, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId);
	~FieldRoom(void);

	void createRoom(void);
};

