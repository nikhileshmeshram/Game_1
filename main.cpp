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
	void init();
	public:
	ControllerC* getInstance();
};

ControllerC* gcntrl = NULL;

ControllerC* ControllerC::getInstance()
{
	if (gcntrl != NULL)
		gcntrl = new ControllerC();
	return gcntrl;	
}

int main()
{
	std::cout<<"lets get started"<<std::endl;
	
	// SCREEN SIZE 80x80
	char pixels[SCREEN_HEIGHT][SCREEN_WIDTH/8];
	memset(pixels,0,SCREEN_HEIGHT*SCREEN_WIDTH/8*sizeof(char));
	// A(5,6)
	int start_x=0;
	int start_y=0;

	// B(10,25)
	int end_x=1;
	int end_y=79;
	
	for (int y=0;y<SCREEN_HEIGHT;y++)
	{
		for(int x=0;x<SCREEN_WIDTH;x++)
		{
			//condition to set (x,y)
			// equation of line y=mx+c
			double m=(end_y-start_y)/(end_x-start_x);
			double c=((start_y*(end_x-start_x))-(start_x*(end_y-start_y)))/(end_x-start_x);
			double proximity=std::abs((y*(end_x-start_x)-x*(end_y-start_y)-start_y*end_x+start_x*end_y)/(end_x-start_x)); 
			//std::cout<<std::abs(6-m*5-c)<<" "<<std::abs(25-m*10-c)<<std::endl;
			if ((x>=start_x && x<=end_x) && (y>=start_y && y<=end_y) && (proximity<=0.707))
			{
				std::cout<<"("<<x<<","<<y<<")"<<std::endl;
				pixels[y][x/8]|=(1<<(7-(x%8)));
			}
		}
	}
	
	for (int y=SCREEN_HEIGHT-1;y>-1;y--)
	{
		for(int x=0;x<SCREEN_WIDTH;x++)
		{
			if (pixels[y][x/8]&(1<<(7-(x%8))))
				std::cout<<" 1";
			else
				std::cout<<" 0";
		}
		std::cout<<std::endl;
	}

	return 0;
}
