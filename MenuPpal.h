#include "Globals.h"

#pragma once
class MenuPpal
{
public:
	MenuPpal(void);
	~MenuPpal(void);
	void pintaMenu();
	void selectOption();
	void changeOption(int o);
	void mostraCredits();
	void mostraInstructions();
	int getOption();

private:
	void drawNormalString(char *s);
	void drawString(char *s);

	int opt;
	bool menu;
};

