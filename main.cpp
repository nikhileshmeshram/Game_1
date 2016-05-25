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
	public:
	DrawablesC():start_x(0),start_y(0)
	{
		width = 0;
		height = 0;
		isDirty=FALSE;
	};
	DrawablesC(int x,int y):start_x(x),start_y(y)
	{
		width = 0;
		height = 0;
		isDirty=FALSE;
	};
	DrawablesC(int x,int y,int w,int h):start_x(x),start_y(y),width(w),height(h){isDirty=FALSE;};

	protected:
	void setWidth(int w)
	{
		width = w;
	};

	void setHeight(int h)
	{
		height = h;
	};
	
	void setDirty(bool b)
	{
		isDirty = b;
	}
		
	int getHeight()
	{
		return height;
	}

	int getWidth()
	{
		return width;
	}
	
	int getStartX()
	{
		return start_x;
	}

	int getStartY()
	{
		return start_y;
	}

	public:
	virtual void draw() = 0;
	//virtual move();
	bool getDirty()
	{
		return isDirty;
	}


	private:
	int start_x;
	int start_y;
	int width;
	int height;
	bool isDirty;
};
//********

//MENUC********
class MenuC : public DrawablesC
{
	static const int bufferWidth = 5;
	static const int bufferHeight = 2;

	std::list<std::string> list_Entries;// Later make a class for each entry
	size_t max_stringlen;
	
	public:
	MenuC():DrawablesC(){max_stringlen = 0;};
	MenuC(int x,int y):DrawablesC(x,y)
	{
		max_stringlen = 0;
		setWidth(bufferWidth);
		setHeight(bufferHeight);
	};
	void addEntry(std::string str)
	{
		size_t  strLen = str.size();
		if (strLen > max_stringlen)
			max_stringlen = str.size();

		list_Entries.push_back(str);

		setWidth(bufferWidth+max_stringlen);
		setHeight(bufferHeight+list_Entries.size());
		//Need to redraw
		setDirty(TRUE);
	}
	
	//Need an undraw too
	void draw()
	{
		//For now use window to create box, otherwise a line can also be used
		WINDOW* myWin = newwin(getHeight(),getWidth(),getStartY(),getStartX());
		box(myWin,0,0);	//Draw Box around window
		wrefresh(myWin);
		delwin(myWin);
		//Need to add entries too
	}
};
//********

//RENDERERC********
class RendererC
{
	friend ControllerC;
	RendererC(){};
	std::list<DrawablesC*> drawList;

	public:
	void init();
	void clear();
	void refresh()
	{
		//TODO Need to maintain a global isDirty for renderer
		//if not dirty return
		
		//Iterate through the drawables and undraw and draw them if they are dirty
		for (std::list<DrawablesC*>::iterator it=drawList.begin(); it != drawList.end(); ++it)
		{
			if ((*it)->getDirty())
			{
				//undraw
				//draw
				(*it)->draw();
			}
		}
	}

	void add(DrawablesC* drwObj)
	{
		drawList.push_back(drwObj);
	}
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
	RendererC* grndr;
	public:
	void init();
	void refresh(DrawablesC* drw)
	{
		grndr->add(drw);
		grndr->refresh();
	}
	void clear();
	static ControllerC* getInstance();
};

ControllerC* gcntrl = NULL;

ControllerC* ControllerC::getInstance()
{
	if (gcntrl == NULL)
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
	int height = 25;
	int width = 50;
	int start_y = (LINES-height)/2;
	int start_x = (COLS-width)/2;
	printw("Press F1 to exit");
	refresh();

	MenuC* firstMenu = new MenuC(start_x,start_y);
	firstMenu->addEntry("Start");
	
	firstMenu->addEntry("Options");
	firstMenu->addEntry("Exit");
	
	(ControllerC::getInstance())->refresh((DrawablesC*) firstMenu);

	int ch;
	while((ch = getch()) != KEY_F(1))
	{
	}
	
	
	(ControllerC::getInstance())->clear();
	return 0;
}
