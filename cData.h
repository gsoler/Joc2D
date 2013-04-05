#pragma once

#include "cTexture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG		8

//Image identifiers
#define IMG_BLOCKS	0
#define IMG_PLAYER	1
#define IMG_SHOT	2
#define IMG_PLAYER2 3
#define IMG_ENEMY1	4
#define IMG_ENEMY2	5
#define IMG_BLOCKS2	6
#define IMG_BLOCKS3	7
/*#define IMG_SHOOT	6
...
*/

class cData
{
public:
	cData(void);
	~cData(void);

	int  GetID(int img);
	void GetSize(int img,int *w,int *h);
	bool LoadImage(int img,char *filename,int type = GL_RGBA);

private:
	cTexture texture[NUM_IMG];
};
