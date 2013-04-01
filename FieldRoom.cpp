#include "FieldRoom.h"
#include "Surface.h"

FieldRoom::FieldRoom(int heigth, int width, int bgTileSize, int fgTileSize, GLuint fgTexId, GLuint bgTexId)
	:Room(heigth, width, bgTileSize, fgTileSize, fgTexId,bgTexId)
{
}


FieldRoom::~FieldRoom(void)
{
}

GLuint FieldRoom::createBackground(unsigned int seed) 
{
	Surface s(height/bgTileSize, width/bgTileSize);
	s.perlinNoise(width/9, seed);

	int id = glGenLists(1);

	glNewList(id, GL_COMPILE);
		glBegin(GL_QUADS);
		for (int i = 0; i < height; i += bgTileSize) {
			for (int j = 0; j < width; j += bgTileSize) {

				float coordx_tile;
				float coordy_tile;
				double z = s.getZ(i, j); 
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

				float px = j;
				float py = i;

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

	return id;
}

GLuint FieldRoom::createForeground(unsigned int seed)
{
	int n = height/fgTileSize;
	int m = width/fgTileSize;
	collisonMap = Matrix(n, vector<int>(m, 0));

	for (int i = 0; i < n; ++i) {
		collisonMap[0][i] = 1;
		collisonMap[m-1][i] = 1;
	}

	for (int i = 0; i < m; ++i) {
		collisonMap[i][0] = 1;
		collisonMap[i][n-1] = 1;
	}

	int id = glGenLists(1);

	glNewList(id, GL_COMPILE);
		glBegin(GL_QUADS);
		for (int i = 0; i < height; i += fgTileSize) {
			for (int j = 0; j < width; j += fgTileSize) {

				float coordx_tile = 0.0f;
				float coordy_tile = 0.0f;

				if (collisonMap[i][j]) {
					float px = j;
					float py = i;

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

	return id;
}

void FieldRoom::createRoom()
{
	bgDisplayList = createBackground(10);
	fgDisplayList = createForeground(10);
}

