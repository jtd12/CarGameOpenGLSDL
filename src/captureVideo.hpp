#ifndef DEF_CAPTUREVIDEO_HPP
#define DEF_CAPTUREVIDEO_HPP
#include "C:\library\SDL2-2.0.12\x86_64-w64-mingw32\include\SDL2\SDL.h"
#include"C:\library\SDL_Image 2.0\include\SDL2\SDL_image.h"
#include<GL/gl.h>
#include<GL/glu.h>
#include<string>
#include<vector>
#include<iostream>
#include <cstdio>

class captureVideo
{
	 int width, height;
    FILE* ffmpeg;
	public:
		captureVideo(int w, int h, int fps, const std::string& filename);
		~captureVideo();
		void captureFrame();
};

#endif
