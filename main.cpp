#include<iostream>
#include<ncurses.h>
#include<cstring>
#include<stdio.h>
#include<cmath> // common
#include<list> // common
#include<string> // common

#define SCREEN_HEIGHT 50
#define SCREEN_WIDTH 50


//forward declarations
class ControllerC;



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
	friend ControllerC;
	RendererC(){};
	std::list<DrawablesC> drawList;

	public:
	void init();
	void clear();
	void refresh();
};

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
	ControllerC()
	{
		mode_m = MainMenu;
		grndr = new RendererC();
	};
	~ControllerC()
	{
		if (grndr)
			delete grndr;
	}
	//Game State
	GMode mode_m;
	RendererC* grndr = NULL;
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
	grndr->init();
}
	
void ControllerC::clear()
{
	grndr->clear();
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
