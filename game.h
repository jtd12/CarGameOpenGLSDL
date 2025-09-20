#ifndef GAME_H
#define GAME_H
#include<string.h>
#include"C:\library\SDL_mixer-1.2.12\include\SDL_mixer.h"
#include <iostream>
#include <conio.h>
#include <sstream>
#include"objloader.h"
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
	 int screenWidth;
	   int screenHeight;
	objloader obj;
	Mix_Music* music;
	int loop;
	float Loop_Point;
	//std::vector< weapon*> weapons;
    SDL_Surface* screen=NULL;
    SDL_Joystick * joystick=NULL;
       SDL_Event event;
	std::vector<level*> levels;
	playerCam* playerCam_;
	std::vector<car*> vehicule;
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
		
		
};
#endif
