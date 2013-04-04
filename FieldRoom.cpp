#include "FieldRoom.h"
#include "Surface.h"

FieldRoom::FieldRoom(int heigth, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId)
	:Room(heigth, width, bgTileSize, fgTileSize, fgTexId, bgTexId)
{
}


FieldRoom::~FieldRoom(void)
{
}

void FieldRoom::createBackground() 
{
	int n = height/bgTileSize;
	int m = width/bgTileSize;

	Surface s(n, m);
	s.perlinNoise(m/2, 0);

	bgDisplayList = glGenLists(1);

	glNewList(bgDisplayList, GL_COMPILE);
		glBegin(GL_QUADS);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				float coordx_tile = 0;
				float coordy_tile = 0;

				double z = s.getZ(j, i); 

				if (z <= -0.5) {
					coordx_tile = 0.0f;
					coordy_tile = 0.0f;
				}
				else if (z <= 0.0) {
					coordx_tile = 0.5f;
					coordy_tile = 0.0f;
				}
				else if (z <= 0.5) {
					coordx_tile = 0.0f;
					coordy_tile = 0.5f;
				}
				else if (z <= 1.0) {
					coordx_tile = 0.5f;
					coordy_tile = 0.5f;
				}

				float px = j*bgTileSize;
				float py = i*bgTileSize;


				glTexCoord2f(coordx_tile, coordy_tile+0.5f);      
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

void FieldRoom::createForeground()
{
	int n = height/fgTileSize;
	int m = width/fgTileSize;

	collisonMap = Matrix(n, vector<int>(m, 0));

	for (int i = 0; i < m; ++i) {
		collisonMap[0][i] = 1;
		collisonMap[n-1][i] = 1;
	}

	for (int i = 0; i < n; ++i) {
		collisonMap[i][0] = 1;
		collisonMap[i][m-1] = 1;
	}

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

					glTexCoord2f(coordx_tile,coordy_tile+0.5f);      
					glVertex2i(px,py);
				
					glTexCoord2f(coordx_tile+0.5f,coordy_tile+0.5f); 
					glVertex2i(px+fgTileSize, py);

					glTexCoord2f(coordx_tile+0.5f,coordy_tile);      
					glVertex2i(px+fgTileSize,py+fgTileSize);
				
					glTexCoord2f(coordx_tile,coordy_tile);           
					glVertex2i(px,py+fgTileSize);
				}
			}
		}
		glEnd();
	glEndList();
}

void FieldRoom::createRoom()
{
	createBackground();
	createForeground();
}

