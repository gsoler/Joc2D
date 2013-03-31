#include "FieldRoom.h"


FieldRoom::FieldRoom(int heigth, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId)
	:Room(heigth, width, bgTileSize, fgTileSize, fgTexId,bgTexId)
{
}


FieldRoom::~FieldRoom(void)
{
}

void FieldRoom::createRoom()
{

}

