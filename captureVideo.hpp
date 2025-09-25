#ifndef DEF_CAPTUREVIDEO_HPP
#define DEF_CAPTUREVIDEO_HPP
#include <C:/library/SDL-1.2.15/include/SDL/SDL.h>
#include <C:/library/SDL_image-1.2.12/include/SDL_image.h>
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
