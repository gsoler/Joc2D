#pragma once
#include <gl/glut.h>

class RoomEntity
{
protected:
	GLuint texId;

	int x;
	int y;

	int h;
	int w;

public:
	RoomEntity(void);
	virtual ~RoomEntity(void);

	void draw();
};

