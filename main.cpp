#include<iostream>
#include<ncurses.h>
#include<cstring>
#include<stdio.h>
#include<cmath>

#define SCREEN_HEIGHT 50
#define SCREEN_WIDTH 50

enum GMode
{
	MainMenu = 0,
	Renderer,
};

class GameStateC
{
	GameStateC();
	
};
class ControllerC
{
	ControllerC(){mode_m = MainMenu;};
	//Game State
	GMode mode_m;
	public:
	void init();
	void clear();
	static ControllerC* getInstance();
};

ControllerC* gcntrl = NULL;

ControllerC* ControllerC::getInstance()
{
	if (gcntrl != NULL)
		gcntrl = new ControllerC();
	return gcntrl;	
}

void ControllerC::init()
{
	initscr();	//Intializes Ncurses module
	cbreak();	//Disable line bufferring
	keypad(stdscr,TRUE);	//Allows special function keys
}
	
void ControllerC::clear()
{
	endwin();
}


class Renderer
{
};

int main()
{
	(ControllerC::getInstance())->init();
	WINDOW* myWin;
	int height = 25;
	int width = 50;
	int start_y = (LINES-height)/2;
	int start_x = (COLS-width)/2;
	printw("Press F1 to exit");
	refresh();
	myWin = newwin(height,width,start_y,start_x);
	box(myWin,0,0);	//Draw Box around window
	wrefresh(myWin);

	int ch;
	while((ch = getch()) != KEY_F(1))
	{
	}
	
	delwin(myWin);
	endwin();
	
//		(ControllerC::getInstance())->clear();
	return 0;
}
