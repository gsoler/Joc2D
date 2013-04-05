#include "MazeRoom.h"
#include "Maze.h"
#include "Surface.h"

MazeRoom::MazeRoom(int heigth, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId)
	:Room(heigth, width, bgTileSize, fgTileSize, fgTexId,bgTexId)
{
}


MazeRoom::~MazeRoom(void)
{
}

void MazeRoom::createBackground(void) 
{
	int n = height/bgTileSize;
	int m = width/bgTileSize;

	Surface s(n, m);
	s.perlinNoise(width/m, 0);

	bgDisplayList = glGenLists(1);

	glNewList(bgDisplayList, GL_COMPILE);
		glBegin(GL_QUADS);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {

				float coordx_tile = 0.0f;
				float coordy_tile = 0.0f;
				
				double z = s.getZ(j, i); 

				if (z <= 0) {
					coordx_tile = 0.0f;
					coordy_tile = 0.0f;
				}
				else if (z <= 0.1) {
					coordx_tile = 0.5f;
					coordy_tile = 0.0f;
				}
				else if (z <= 0.2) {
					coordx_tile = 0.0f;
					coordy_tile = 0.5f;
				}
				else if (z <= 1.0) {
					coordx_tile = 0.5f;
					coordy_tile = 0.5f;
				}

				float px = j*bgTileSize;
				float py = i*bgTileSize;

				glTexCoord2f(coordx_tile,coordy_tile+0.5f);      
				glVertex2i(px,py);
				
				glTexCoord2f(coordx_tile+0.5f,coordy_tile+0.5f); 
				glVertex2i(px+bgTileSize, py);

				glTexCoord2f(coordx_tile+0.5f,coordy_tile);      
				glVertex2i(px+bgTileSize,py+bgTileSize);
				
				glTexCoord2f(coordx_tile,coordy_tile);           
				glVertex2i(px,py+bgTileSize);
			}
		}
		glEnd();
	glEndList();
}

void MazeRoom::createForeground(void)
{
	int n = height/fgTileSize;
	int m = width/fgTileSize;
	collisonMap = Matrix(n, vector<int>(m, 0));

	Maze maze(n,m,0,0);
	maze.generateMaze(0);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			collisonMap[i][j] = maze.isWall(j, i);
		}
	}
	
	collisonMap[0][m/2] = 0;
	collisonMap[0][m/2 - 1] = 0;

	collisonMap[n-1][m/2] = 0;
	collisonMap[n-1][m/2 - 1] = 0;


	fgDisplayList = glGenLists(1);

	glNewList(fgDisplayList, GL_COMPILE);
		glBegin(GL_QUADS);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {

				float coordx_tile = 0.0f;
				float coordy_tile = 0.0f;

				if (collisonMap[i][j]) {
					float px = j*fgTileSize;
					float py = i*fgTileSize;

					glTexCoord2f(coordx_tile,coordy_tile+1.0f);      
					glVertex2i(px,py);
				
					glTexCoord2f(coordx_tile+1.0f,coordy_tile+1.0f); 
					glVertex2i(px+fgTileSize, py);

					glTexCoord2f(coordx_tile+1.0f,coordy_tile);      
					glVertex2i(px+fgTileSize,py+fgTileSize);
				
					glTexCoord2f(coordx_tile,coordy_tile);           
					glVertex2i(px,py+fgTileSize);
				}
			}
		}
		glEnd();
	glEndList();
}

void MazeRoom::createRoom(void)
{
	createBackground();
	createForeground();
}