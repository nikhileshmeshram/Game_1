#include<iostream>
#include<ncurses.h>
#include<cstring>
#include<stdio.h>
#include<cmath> // common
#include<list> // common
#include<string> // common

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

//DRAWABLESC********
class DrawablesC
{
	protected:
	DrawablesC():start_x(0),start_y(0){};
	DrawablesC(int x,int y):start_x(x),start_y(y){};
	// virtual draw();
	// virtual move();
	private:
	int start_x;
	int start_y;
};
//********

//MENUC********
class MenuC:DrawablesC
{
	MenuC():DrawablesC(){};
	MenuC(int x, int y):DrawablesC(x,y){};

	std::list<std::string> Entries;// Later make a class for each entry
};
//********

//RENDERERC********
class RendererC
{
	RendererC(){};
	std::list<DrawablesC> drawList;

	public:
	static RendererC* getInstance();
	void init();
	void clear();
	void refresh();
};

RendererC* grndr = NULL;

RendererC* RendererC::getInstance()
{
	if (grndr != NULL)
		grndr = new RendererC();
	return grndr;	
}

void RendererC::init()
{
	initscr();	//Intializes Ncurses module
	cbreak();	//Disable line bufferring
	keypad(stdscr,TRUE);	//Allows special function keys
}

void RendererC::clear()
{
	endwin();
}
//********

//CONTROLLERC********
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
	RendererC::getInstance()->init();
}
	
void ControllerC::clear()
{
	RendererC::getInstance()->clear();
}
//********





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
	
	(ControllerC::getInstance())->clear();
	return 0;
}
