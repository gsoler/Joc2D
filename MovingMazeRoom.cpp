
#include "MovingMazeRoom.h"


MovingMazeRoom::MovingMazeRoom(int heigth, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId)
	: MazeRoom(heigth, width, bgTileSize, fgTileSize, fgTexId,bgTexId)
{
}


MovingMazeRoom::~MovingMazeRoom(void)
{
}

void MovingMazeRoom::createRoom(void) 
{
	MazeRoom::createRoom();

	int nBlocks = 10;

	int n = collisonMap.size();
	int m = collisonMap[0].size();

	for (int i = 0; i < n && nBlocks > 0; ++i) {
		for (int j = 0; j < m && nBlocks > 0; ++j) {
			if (collisonMap[i][j] == 0) {
				blocks.push_back(Vec2(j*fgTileSize, i*fgTileSize));
				--nBlocks;
			}
		}
	}
}

void MovingMazeRoom::drawBlock(Vec2 b) 
{
	
	float px = b.first;
	float py = b.second;

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,bgTexId);
	glBegin(GL_QUADS);	
		float coordx_tile = 0.0f;
		float coordy_tile = 0.0f;

		glTexCoord2f(coordx_tile,coordy_tile+0.5f);      
		glVertex2i(px,py);
				
		glTexCoord2f(coordx_tile+0.5f,coordy_tile+0.5f); 
		glVertex2i(px+fgTileSize, py);

		glTexCoord2f(coordx_tile+0.5f,coordy_tile);      
		glVertex2i(px+fgTileSize,py+fgTileSize);
				
		glTexCoord2f(coordx_tile,coordy_tile);           
		glVertex2i(px,py+fgTileSize);
	glEnd();

	glDisable(GL_TEXTURE_2D);

}

void MovingMazeRoom::drawRoom(GLuint texBullets, GLuint texEnemy1, GLuint texEnemy2) {

	Room::drawRoom(texBullets, texEnemy1, texEnemy2);

	for (Iter it = blocks.begin(); it != blocks.end(); ++it) {
		drawBlock(*it);
	}
}

void MovingMazeRoom::procces(void) 
{
	for (Iter it = blocks.begin(); it != blocks.end(); ++it) {
		
	}
}