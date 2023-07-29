#ifndef CAR_H
#define CAR_H
#include <C:/library/SDL-1.2.15/include/SDL/SDL.h>
#include<C:\library\SDL_ttf-2.0.11\include\SDL_ttf.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include"vector.h"
#include"collisionplane.h"
#include"collisionsphere.h"
#include"camera.h"
#include<string>
#include<vector>
#include<math.h>
#include"collision.h"
#define ni 8

class car
{
	int mesh;
	std::string name;
	collisionsphere cs;
	int health;
	vector3d force;
	vector3d direction;
	bool isground,iscollision, issprint;
	float sprintspeed,normalspeed;
	float lookspeed;
	float energy;
	int points;
	int curWeapon;
	bool isWeapon;
	vector3d pos;
	float acc, dec,dec2;
	float s;
	vector3d a;
	vector3d loc;
	int point[ni][2];
	int n;
	int up,down,left,right,clavierAct,a_touch;
 	float angle;
	float turnSpeed;
	float speed;
	float maxSpeed;	
	float speedJoy;
	bool  joyInputActive;
	bool joyTurn;
	camera cam;
	public:

car(unsigned int name, const char* n,collisionsphere ccs, float sprints,float normals,float looks);
		~car();
		void update(std::vector<collisionplane>& collplane);
		void show();
		void setPosition(vector3d pos);
			void setLocation(vector3d vec);
			vector3d getLocation();
			void control();
			void move();
			void setRotation(vector3d r);
			vector3d getRotation();
			int getUP();
			int getDOWN();
			int getRIGHT();
			int getLEFT();
			int getClavierAct();
			void setUP(int num);
			void setDOWN(int num);
			void setRIGHT(int num);
			void setLEFT(int num);
			void setA(int A);
			int getA();
			void moveai();
			void initialiseai();
		float setSpeed(float num);
		void setSpeed(float s,float speedJoy);
		void moveAI();
		float getSpeed();
		float getMaxSpeed();
		void setjoy(float j);
		void setJoyTurnSpeed(bool a);
		void setTurn(bool a);
		bool getTurn();
		float getJoy();
	};
	#endif
