#include "camera.h"

void camera::lockCamera()
{
	if(camPitch>90)
		camPitch=90;
	if(camPitch<-90)
		camPitch=-90;
	if(camYaw<0.0)
		camYaw+=360.0;
	if(camYaw>360.0)
		camYaw-=360;
}

void camera::moveCamera(float dir)
{
	float rad=(camYaw+dir)*M_PI/180.0;
loc.x -= sin(rad) * movevel;
    loc.z -= cos(rad) * movevel;
    
}

void camera::moveCameraUp(float dir)
{
	float rad=(camPitch+dir)*M_PI/180.0;
	loc.y+=sin(rad)*movevel;	
}

camera::camera()
{
	camPitch=0;
	camYaw=0;
	movevel=0.2;
	mousevel=0.2;
	mi=ismoved=false;
		mi=false;
	speed=0.2;
	maxSpeed=20;
dec=0.09;
	acc=0.04;
	up=0;
	down=0;
	a=0;
}
camera::camera(vector3d l)
{
	loc.change(l);
	camPitch=0;
	camYaw=0;
	movevel=0.2;
	mousevel=0.2;
	mi=ismoved=false;
		mi=false;
	speed=0.2;
	maxSpeed=20;
dec=0.09;
	acc=0.04;
	up=0;
	down=0;
	a=0;
}

camera::camera(vector3d l,float yaw,float pitch)
{
	loc.change(l);
	camPitch=pitch;
	camYaw=yaw;
	movevel=0.2;
	mousevel=0.2;
	mi=ismoved=false;
		mi=false;
	speed=0.2;
	maxSpeed=20;
dec=0.09;
	acc=0.04;
	up=0;
	down=0;
	a=0;
}

camera::camera(vector3d l,float yaw,float pitch,float mv,float mov)
{
	loc.change(l);
	camPitch=pitch;
	camYaw=yaw;
	movevel=speed;
	mousevel=mov;
	mi=false;
	speed=0.2;
	maxSpeed=20;
dec=0.09;
	acc=0.04;
	up=0;
	down=0;
	a=0;
}

void camera::Control()
{
	
	if(mi)
	{
		int MidX=320;
		int MidY=240;
		SDL_ShowCursor(SDL_DISABLE);
		int tmpx,tmpy;
		SDL_GetMouseState(&tmpx,&tmpy);
		camYaw+=mousevel*(MidX-tmpx);
		camPitch+=mousevel*(MidY-tmpy);
		lockCamera();
		SDL_WarpMouse(MidX,MidY);
		Uint8* state=SDL_GetKeyState(NULL);
		ismoved=false;
	
				
		if(state[SDLK_w])
		{
			
	
			up=1;
			
				ismoved=true;

			
			//moveCameraUp(0.0);
		}
	
		else if(state[SDLK_w]==false)
		{
			up=0;
		}
	
	}



			
    //glTranslated(-loc.x,-loc.y,-loc.z);
	glRotatef(-camPitch,1.0,0.0,0.0);
	glRotatef(-camYaw,0.0,1.0,0.0);
	

	
}

void camera::UpdateCamera()
{
	/*
	
		if(up==1)
		{
				if( movevel<maxSpeed)
			{
				if(movevel<0)
				{
					movevel+=dec;
				}
				else
				{
					movevel+=acc;
				}
			}
		
	     	
	     }
	     	if(down==1 && movevel>-maxSpeed)
			{
				if(movevel>0)
				{
					movevel-=dec;
				}
				else
				{
					movevel-=acc;
				}
				
			}
	     moveCamera(0);
	     
	     if(up==0 )
			{
				if(movevel-dec>0)
				{
					movevel-=dec;
				}
				else if(movevel+dec<0)
				{
					movevel+=dec;
				}
				else
				{
					movevel=0;
				}
				
			}
		
				*/
			
	glTranslatef(-loc.x,-loc.y,-loc.z);
}

//change the spherical coordinate system to cartesian
vector3d camera::getVector()
{
	//Google->spherical to cartesian
 	return (vector3d(-cos(camPitch*M_PI/180.0)*sin(camYaw*M_PI/180.0),sin(camPitch*M_PI/180.0),-cos(camPitch*M_PI/180.0)*cos(camYaw*M_PI/180.0)));
}
vector3d camera::getLocation()
{
	return loc;
}

float camera::getPitch()
{
	return camPitch;
}

float camera::getYaw()
{
	return camYaw;
}
void camera::setYaw(float cYaw)
{
	camYaw+=cYaw;
}
void camera::setYawReset(float cYaw)
{
	camYaw=cYaw;
}
void camera::setPitch(float cYaw)
{
	camPitch+=cYaw;
}
void camera::setPitchReset(float cYaw)
{
	camPitch=cYaw;
}
float camera::getMovevel()
{
	return movevel;
}
float camera::getMousevel()
{
	return mousevel;
}

bool camera::isMouseIn()
{
	return mi;
}
		
void camera::setLocation(vector3d vec)
{
	loc.change(vec);
}

void camera::lookAt(float pitch,float yaw)
{
	camPitch=pitch;
	camYaw=yaw;
}

void camera::mouseIn(bool b)
{
	mi=b;
}

void camera::setSpeed(float mv,float mov)
{
	movevel=mv;
	mousevel=mov;
}

bool camera::isMoved()
{
	return ismoved;
}
