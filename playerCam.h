#ifndef DEF_PLAYERCAM_H
#define DEF_PLAYERCAM_H
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
#include<C:/freeglut/include/GL/glut.h>
#define pi 3.14159265359 // on definit un nombre pi

class playerCam
{
public:
	playerCam(const char * n,collisionsphere ccs,float sprints,float normals,float looks);
	~playerCam();
	camera cam;
		void update(std::vector<collisionplane>& collplane);
	void show();
	 	collisionsphere getCollissionSphere();
	 		void setPosition(vector3d pos);
	 		collisionsphere cs;
	 			void setLocation(vector3d  loc);
			vector3d getLocation();
			void inputSpecial(char key,int x, int y);
			void setJump();
			void setSprint();
			void stopSprint();
			void relacherSpecial(char key,int x, int y);
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
		float energy;
		float 	sprintspeed;
		float normalspeed;
		vector3d direction,rotation;
		
};
#endif
