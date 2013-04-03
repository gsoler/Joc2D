
#include "cPlayer.h"

cPlayer::cPlayer() {}
cPlayer::~cPlayer(){}

void cPlayer::Draw(int tex_id)
{	
	float xo,yo,xf,yf;

	switch(GetState())
	{
		//1
		case STATE_LOOKUP:			xo = 1.0f/6.0f;	yo = 4.0f/8.0f;
									break;
		//4
		case STATE_LOOKUPRIGHT:		xo = 1.0f/6.0f;	yo = 0.0f/8.0f;
									break;
		//1	
		case STATE_LOOKRIGHT:		xo = 1.0f/6.0f;	yo = 3.0f/8.0f;
									break;
		//4
		case STATE_LOOKDOWNRIGHT:	xo = 1.0f/6.0f;	yo = 6.0f/8.0f;
									break;
		//1
		case STATE_LOOKDOWN:		xo = 1.0f/6.0f;	yo = 1.0f/8.0f;
									break;
		//4
		case STATE_LOOKDOWNLEFT:	xo = 1.0f/6.0f;	yo = 5.0f/8.0f;
									break;
		//1
		case STATE_LOOKLEFT:		xo = 1.0f/6.0f;	yo = 2.0f/8.0f;
									break;
		//4
		case STATE_LOOKUPLEFT:		xo = 1.0f/6.0f;	yo = 7.0f/8.0f;
									break;


		//1..3
		case STATE_WALKUP:			xo = 1.0f/6.0f + (GetFrame()*1.0f/6.0f); yo = 4.0f/8.0f;
									NextFrame(6);
									break;
		//4..6
		case STATE_WALKUPRIGHT:		xo = 1.0f/6.0f + (GetFrame()*1.0f/6.0f); yo = 0.0f/8.0f;
									NextFrame(6);
									break;
		//1..3
		case STATE_WALKRIGHT:		xo = 1.0f/6.0f + (GetFrame()*1.0f/6.0f); yo = 3.0f/8.0f;
									NextFrame(6);
									break;
		//4..6
		case STATE_WALKDOWNRIGHT:	xo = 1.0f/6.0f + (GetFrame()*1.0f/6.0f); yo = 6.0f/8.0f;
									NextFrame(6);
									break;
		//1..3
		case STATE_WALKDOWN:		xo = 1.0f/6.0f + (GetFrame()*1.0f/6.0f); yo = 1.0f/8.0f;
									NextFrame(6);
									break;
		//4..6
		case STATE_WALKDOWNLEFT:	xo = 1.0f/6.0f + (GetFrame()*1.0f/6.0f); yo = 5.0f/8.0f;
									NextFrame(6);
									break;
		//1..3
		case STATE_WALKLEFT:		xo = 1.0f/6.0f + (GetFrame()*1.0f/6.0f); yo = 2.0f/8.0f;
									NextFrame(6);
									break;
		//4..6
		case STATE_WALKUPLEFT:		xo = 1.0f/6.0f + (GetFrame()*1.0f/6.0f); yo = 7.0f/8.0f;
									NextFrame(6);
									break;
	}
	xf = xo + 1.0f/6.0f;
	yf = yo - 1.0f/8.0f;

	DrawRect(tex_id,xo,yo,xf,yf);
}
