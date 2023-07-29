#ifndef CAMERA_H
#define CAMERA_H
#include <cmath>
#include <iostream>
#include <C:/library/SDL-1.2.15/include/SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "vector.h"

class camera{


	float movevel;
	float mousevel;
	bool mi,ismoved;
	void lockCamera();
	void moveCamera(float dir);
	void moveCameraUp(float dir);
		float speed;
		float a;
	float maxSpeed;
	float dec;
	float acc;
	bool up,down;
	vector3d loc;
	float camPitch,camYaw;
	
	public:

		camera();
		camera(vector3d loc);
		camera(vector3d loc,float yaw,float pitch);
		camera(vector3d loc,float yaw,float pitch,float mv,float mov);
		void Control();
		void UpdateCamera();
		vector3d getVector();
		vector3d getLocation();
		float getPitch();
		float getYaw();
		void setYaw(float cYaw);
		void setPitch(float cYaw);
		void setYawReset(float cYaw);
		void setPitchReset(float cYaw);
		float getMovevel();
		float getMousevel();
		bool isMouseIn();
		void setLocation(vector3d vec);
		void lookAt(float pitch,float yaw);
		void mouseIn(bool b);
		void setSpeed(float mv,float mov);
		bool isMoved();
};

#endif
