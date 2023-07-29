#include"car.h"

car::car(unsigned int name_, const char* n,collisionsphere ccs, float sprints,float normals,float looks)
	{
		mesh=name_;
		name=n;
		cs=ccs;
		sprintspeed=sprints;
		normalspeed=normals;
		force.change(0.0,-0.5,0.0);
		setPosition(vector3d(cs.center));
		setSpeed(normalspeed,looks);
		points=0;
		energy=10;
		isground=iscollision=issprint=false;
		health=100;
		speed=normals;
		angle=0;
		maxSpeed=8.0;
		acc=0.04;
		dec=0.05;
		dec2=0.25;
		turnSpeed=5.1;
		up=0;
		down=0;
		left=0;
		right=0;
		clavierAct=0;
		s=0;
		a=vector3d(0,0,0);
		a_touch=0;
		//weapons.push_back(wep);
	//	curWeapon=0;
		//isWeapon=true;
		
	}
	void car::show()
	{
		glPushMatrix();


		glTranslated(getLocation().x,getLocation().y,getLocation().z);
		glRotated(getRotation().y,0,1.0,0);
			//glCallList(mesh);
		
			glPopMatrix();
	}
		car::~car()
		{
		}
		void car::update(std::vector<collisionplane>& collplane)
		{
				if(getLocation().y<5)
		{
			setPosition(vector3d(getLocation().x,50,getLocation().z));
		
			speed=0.0f;
		}
		if(direction.y>=force.y)
			
				direction+=force;
			//setPosition(cs.center+direction);	
			vector3d newPos(getLocation());
			newPos+=direction;
			for(int i=0;i<collplane.size();i++)
				collision::sphereplane(newPos,collplane[i].normal,collplane[i].p[0],collplane[i].p[1],collplane[i].p[2],collplane[i].p[3],cs.r);
				
				 if(getLocation().y<newPos.y)
				  isground=true;
				  else
				   isground=false;
		    	setPosition(newPos);
	
			//setPosition(cs.center+direction);	
		
		
		    /*	if(isWeapon)
		    	
		        	weapons[curWeapon]->update();
					*/
		}
	
		void car::setPosition(vector3d pos)
		{
			cs.center=pos;
			setLocation(pos);
		}
	
		vector3d car::getLocation()
{
	return loc;
}

vector3d car::getRotation()
 {
 	return vector3d(a.x,a.y,a.z);
 }
 void car::setRotation(vector3d r)
 {
 	a=r;
 }
void car::setLocation(vector3d vec)
{
	loc.change(vec);
}
   void car::move()
   {
    loc.x -= cos(a.y*M_PI/180) * s;
    loc.z += sin(a.y*M_PI/180) * s;
  
   }
   
void car::control()
{
		Uint8* state=SDL_GetKeyState(NULL);
			if(state[SDLK_m])
			{
					clavierAct++;
				
				}
					if(clavierAct>3)
					{
						clavierAct=0;
					}
				if(clavierAct==1)
				{
				
		if(state[SDLK_z])
		{
			
	
			up=1;
			
		

			
			//moveCameraUp(0.0);
		}
			if(state[SDLK_z]==false)
		{
			
	
			up=0;
			
		

			
			//moveCameraUp(0.0);
		}
		
			if(state[SDLK_w])
		{
			
	
			down=1;
			
		

			
			//moveCameraUp(0.0);
		}
			if(state[SDLK_w]==false)
		{
			
	
			down=0;
			
		

			
			//moveCameraUp(0.0);
		}
		
				if(state[SDLK_q])
		{
			
	
			left=1;
			
		

			
			//moveCameraUp(0.0);
		}
			if(state[SDLK_q]==false)
		{
			
	
			left=0;
			
		

			
			//moveCameraUp(0.0);
		}
		
				if(state[SDLK_d])
		{
			
	
			right=1;
			
		

			
			//moveCameraUp(0.0);
		}
			if(state[SDLK_d]==false)
		{
			
	
			right=0;
			
		

			
			//moveCameraUp(0.0);
		}
		
	}
			if(up==1 && speed<maxSpeed)
			{
				if(speed<0)
				{
					speed+=dec;
			 }
				else
				{
					speed+=acc;
				}
			}
			if(down==1 && speed>-maxSpeed)
			{
				if(speed>0)
				{
					speed-=dec;
				}
				else
				{
					speed-=acc;
				}
				
			}
			
			if(up==0 && down==0)
			{
				if(speed-dec>0)
				{
					speed-=dec;
				}
				else if(speed+dec<0)
				{
					speed+=dec;
				}
				else
				{
					speed=0;
				}
			}
			
				if(a_touch==1)
			{
				if(speed-dec2>0)
				{
					speed-=dec2;
				}
				else if(speed+dec2<0)
				{
					speed+=dec2;
				}
				else
				{
					speed=0;
				}
			}
	if(joyTurn)
	{
		angle+=speedJoy;
	}
		if(right)
	{

		angle+=turnSpeed*(speed/maxSpeed);
		//angle=turnSpeed;
		

	
	
	//	+=turnSpeed*(speed/maxSpeed);
	}
		if(left)
	{
		angle-=turnSpeed*(speed/maxSpeed);
	}
		s=speed;
		a.y=angle;
		move();
		
	
}

int car::getUP()
{
	return up;
	
}
int car::getDOWN()
{
	return down;
	
}
int car::getRIGHT()
{
	return right;
	
}
int car::getLEFT()
{
	return left;
	
}
int car::getA()
{
	return a_touch;
}
void car::setA(int A)
{
	a_touch=A;
}
int car::getClavierAct()
{
	return clavierAct;
}
void car::setUP(int num)
{
	up=num;
}
void car::setDOWN(int num)
{
	down=num;
}
void car::setRIGHT(int num)
{
	right=num;
}
void car::setLEFT(int num)
{
	left=num;
}


 float car::getSpeed()
 {
 	return speed;
 }
void car::setSpeed(float s,float speedJoy)
{
	speed=s*speedJoy;
}
bool car::getTurn()
 {
 	return joyInputActive;
 }
 void car::setTurn(bool a)
 {
 joyInputActive=a;
 }
 void car::setjoy(float j)
 {
 	speedJoy=j;
 }
 float car::getJoy()
 {
 	return speedJoy;
 }
float car::getMaxSpeed()
{
	return maxSpeed;
}
void car::setJoyTurnSpeed(bool a)
{
	joyTurn=a;
}

  
