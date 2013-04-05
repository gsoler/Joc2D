#include "MenuPpal.h"


MenuPpal::MenuPpal(void)
{
	opt = 1;
	menu = true;
}


MenuPpal::~MenuPpal(void)
{
}

int MenuPpal::getOption()
{
	return opt;
}

void MenuPpal::drawString (char *s)
{
	unsigned int i;
	for (i=0; i<strlen(s); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
}

void MenuPpal::drawNormalString (char *s)
{
	unsigned int i;
	for (i=0; i<strlen(s); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
}

void MenuPpal::mostraInstructions()
{	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 0.0f);
	glRasterPos2f(-0.1f, 0.4f);
	drawString("Intruccions");
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(-0.4f, 0.3f);
	drawNormalString("Utilitza les fletxes per a moure el jugador 1,");
	glRasterPos2f(-0.4f, 0.2f);
	drawNormalString("amb els botons, 'a' 's' 'd' i 'w' mou el jugador 2");
	glRasterPos2f(-0.4f, 0.1f);
	drawNormalString("per a disparar utilitza el boto '-' per al jugador 1,");
	glRasterPos2f(-0.4f,0.0f);
	drawNormalString("i espai amb el jugador 2, per a jugar amb un unic");
	glRasterPos2f(-0.4f,-0.1f);
	drawNormalString("jugador, apreta el boto 'p', i esc per a tornar enrere.");

	glutSwapBuffers();
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void MenuPpal::mostraCredits()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 0.0f);
	glRasterPos2f(-0.1f, 0.4f);
	drawString("Credits");
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(-0.2f, 0.3f);
	drawNormalString("Genis Sole");
	glRasterPos2f(-0.2f, 0.2f);
	drawNormalString("Gerard Soler");
	
	glutSwapBuffers();
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void MenuPpal::pintaMenu()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	
		glClear(GL_COLOR_BUFFER_BIT);
		if(opt == 1) glColor3f(0.0f, 1.0f, 0.0f);
		else glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos3f(-0.05f, 0.15f,0.0f);
		drawString("Juga");

		if(opt == 2) glColor3f(0.0f, 1.0f, 0.0f);
		else glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos2f(-0.05f, 0.05f);
		drawString("Instruccions");

		if(opt == 3) glColor3f(0.0f, 1.0f, 0.0f);
		else glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos2f(-0.05f, -0.05f);
		drawString("Credits");

		if(opt == 4) glColor3f(0.0f, 1.0f, 0.0f);
		else glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos2f(-0.05f, -0.15f);
		drawString("Surt");
	glutSwapBuffers();
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void MenuPpal::changeOption(int o)
{
	opt = o;
}

