#ifndef DEF_BOTTON_HPP
#define DEF_BOUTTON_HPP
#include <iostream>
#include "C:\library\SDL2-2.0.12\x86_64-w64-mingw32\include\SDL2\SDL.h"
#include"C:\library\SDL2_ttf-2.19.3\x86_64-w64-mingw32\include\SDL2\SDL_ttf.h"
#include<GL/gl.h>
#include<GL/glu.h>


class boutton
{


    int minX, minY;
    int maxX,maxY;
    
	public:
		boutton(int minX,int maxX,int minY,int maxY);
		~boutton();
		void unset2D();
		void set2D(int width, int height);
		void drawButton(int x, int y, int w, int h, bool hovered);
		int getMinX();
		int getMinY();
		int getMaxX();
		int getMaxY();


	
};
#endif
