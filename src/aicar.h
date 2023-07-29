#ifndef AICAR_H
#define AICAR_H
#include <GL/gl.h>
#include <GL/glu.h>
#include<vector>
#include"vector.h"
#include"collision.h"
#include"collisionsphere.h"
#include"collisionplane.h"
#include<cmath>
#include<iostream>
#define pi 3.14159265359 // on definit un nombre pi


class carAI
{
	public:
		carAI(std::vector<unsigned int>& anim,float sp,collisionsphere css);
		~carAI();
		void show();
		void update(std::vector<collisionplane>& collplane);
		collisionsphere * getCollisionSphere();
		void setLocation(vector3d newLoc);
		private:
	std::vector<unsigned int > frames;
	float walk;
	float curFrame;
	float speed;
	vector3d direction,rotation;
	collisionsphere cs;

			
		
};
#endif
