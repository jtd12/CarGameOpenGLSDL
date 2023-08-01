#ifndef GAME_H
#define GAME_H
#include<string.h>
#include <iostream>
#include <conio.h>
#include <sstream>
#include"objloader.h"
#include"C:\library\glad\include\glad\glad.h"
#include "C:\library\SDL2-2.0.12\x86_64-w64-mingw32\include\SDL2\SDL.h"
#include"C:\library\SDL2_ttf-2.19.3\x86_64-w64-mingw32\include\SDL2\SDL_ttf.h"
#include"C:\library\SDL2_mixer-2.5.3\x86_64-w64-mingw32\include\SDL2\SDL_mixer.h"
#include"text.h"
#include"vector.h"
#include"collisionplane.h"
#include"collisionsphere.h"
#include"camera.h"
#include"level.h"
#include"player.h"
#include"car.h"

#define LARGEUR 1260
#define HAUTEUR 740

class game
{
	 int screenWidth=960;
     int screenHeight=540;
	objloader obj;
	

    SDL_Window* pWindow{ nullptr };     
    SDL_Renderer* pRenderer{ nullptr };

	int loop;
	float Loop_Point;
	//std::vector< weapon*> weapons;
    SDL_Surface* screen=NULL;
    SDL_Joystick * joystick=NULL;
       SDL_Event event;
	std::vector<level*> levels;
	playerCam* playerCam_;
	std::vector<car*> vehicule;
	Mix_Music* music;
	void update();
	void audio();
	void show();
	void RenderText(std::string message, SDL_Color color, int x, int y,float x2,float y2, int size);
	void MakeShadowMatrix(GLfloat points_plan[3][3], GLfloat lightPos[4], GLfloat destMat[4][4]);
	void Normale(float v[3][3], float out[3]);
	void Vecteur_Unite(float vector[3]);
	void lighting();
	std::string float2str(float x);
	
	
	public:
		game();
	~game();
		void start();
		bool initSDL();
		void resizeWindow(int windowWidth, int windowHeight);
		
		
};
#endif
