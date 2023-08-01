#ifndef PLAYERCAM_H
#define PLAYERCAM_H
#include <GL/gl.h>
#include <GL/glu.h>
#include<vector>
#include"vector.h"
#include"collision.h"
#include"collisionsphere.h"
#include"collisionplane.h"
#include"camera.h"
#include<cmath>
#include<iostream>
#define pi 3.14159265359 // on definit un nombre pi

class playerCam
{
public:
	playerCam(const char * n,collisionsphere ccs,float sprints,float normals,float looks);
	~playerCam();
	camera cam;
		void update(std::vector<collisionplane>& collplane);
		void setAroundTouch(int b);
		void setAroundTouch2(int b);
		void setAroundTouch3(int b);
		void setAroundTouch4(int b);
	void show();
	 	collisionsphere getCollissionSphere();
	 		void setPosition(vector3d pos);
	 		collisionsphere cs;
	 			void setLocation(vector3d  loc);
			vector3d getLocation();
			void orbit();
			void setJump();
			void setSprint();
			void stopSprint();
private:
		unsigned int w;
		float speed;
	std::vector<unsigned int> frames;
	unsigned int a_;
	bool up,down,right,left;
	float curFrame;
	std::string name;
	int mesh;
	std::string file_;
		vector3d force;
	bool isground,iscollision, issprint;
		vector3d loc;
		float rot;
		float 	sprintspeed;
		float normalspeed;
		vector3d direction,rotation;
		float energy;
		int touchAround,touchAround2,touchAround3,touchAround4;
		
};
#endif

