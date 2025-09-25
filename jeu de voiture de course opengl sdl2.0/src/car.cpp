#include"car.h"

car::car(unsigned int name_, const char* n, float sprints,float normals,float looks,objloader* terrain)
	{
		mesh=name_;
		name=n;
		sprintspeed=sprints;
		normalspeed=normals;
		loc.x = 20;
		loc.z = 100;
		carSphere = { loc, 10.0f };
		
		// Mettre à jour la hauteur et la sphère
		loc.y = terrain->getHeightAt(loc.x, loc.z) +30.0f;
		carSphere.center = loc;
		setSpeed(normalspeed,looks);
		points=0;
		energy=10;
		isground=iscollision=issprint=false;
		health=100;
		speed=normals;
		angle=0;
		maxSpeed=3.5f;
		acc=0.008f;
		dec=0.005;
		dec2=0.08;
		turnSpeed=3.0f;
		up=0;
		down=0;
		left=0;
		right=0;
		clavierAct=0;
		s=0;
		a=vector3d(0,0,0);
		a_touch=0;
		 velocity=vector3d(0,0,0);
		deltaTime=1.0f;
		
		//weapons.push_back(wep);
	//	curWeapon=0;
		//isWeapon=true;
		
	}
	void car::show()
	{
		glPushMatrix();


		glTranslated(getLocation().x,getLocation().y,getLocation().z);
		glRotated(getRotation().y,0,1.0,0);
		glCallList(mesh);
		
		glPopMatrix();
	}
		car::~car()
		{
		}
		



		void car::update(const std::vector<CollisionTriangle>& collisionMesh,objloader* terrain)
		{
	bool collisionFloor=false;

	float dist;
	float dt = 0.16f;
	int subSteps = 3;  // plus de sous-pas = moins de risque de traverser
    float stepDt = dt / subSteps;
    
	

    for (int i = 0; i < subSteps; i++)
    {
        // Déplacement provisoire (sans gravité pour l'instant)
        vector3d nextLoc = loc + velocity * stepDt;

        // Détection du terrain
        float rayStartY = std::max(loc.y, nextLoc.y) + carSphere.radius + 30.0f;
        vector3d rayStart(loc.x, rayStartY, loc.z);
        float terrainY = collision::raycastDown(rayStart, terrain->collisionMesh);

        if (terrainY != -FLT_MAX) 
        {
            float minHeight = terrainY + carSphere.radius;        // juste au-dessus du sol
            float maxHeight = terrainY + carSphere.radius + 2.0f; // limite max

            if (nextLoc.y < minHeight) 
            {
                // ?? Sous le sol ? replacer et PAS de gravité
                nextLoc.y = minHeight;
                velocity.y = 0;
                isground = true;
            }
       
            else if (nextLoc.y > maxHeight) 
            {
                // ? Trop haut ? limiter
                nextLoc.y = maxHeight;
                velocity.y = 0;
                isground = true;
            }
            else 
            {
            	
            	if(nextLoc.y>0)
            	{
				
                // ? Dans l’air au-dessus du sol ? appliquer gravité
                velocity.y += -9.81f * stepDt;
                isground = false;
            }
            }
        }
        else
        {
            //
			if(nextLoc.y>0)
            	{
			
            velocity.y += -9.81f * stepDt;
            isground = false;
        }
        }

        // Mise à jour position
        loc = nextLoc;
        carSphere.center = loc;
        
        
	if (loc.y < 0.0f) {
	    loc.y += 20.0f;      // remonter de 10 unités
	    velocity.y = 0.0f;   // annuler toute vitesse verticale
	    isground = true;
	    carSphere.center = loc; // mettre à jour la sphère aussi
	}
	
	if (loc.y > 40.0f) {
    loc.y = 40.0f;       // limite max
    velocity.y = 0.0f;   // on annule la vitesse verticale
    carSphere.center = loc; // mise à jour de la sphère
		}
	}	

    

}
	
	
	void car::update2(const std::vector<CollisionTriangle>& collisionMesh)
	{

	bool collisionBlock=false;
	float dist;
	float dt = 0.16f;
	int subSteps = 3;  // plus de sous-pas = moins de risque de traverser
    float stepDt = dt / subSteps;
    


    // Mouvement provisoire
    vector3d nextLoc = loc + velocity * stepDt;
    
    
	for (const auto& tri : collisionMesh) {
 
	
	    float dist = collision::distancePointTriangle(loc, tri.v0, tri.v1, tri.v2);
	   if (dist < 5) {
        // collision !
        	vector3d edge1 = tri.v1 - tri.v0;
            vector3d edge2 = tri.v2 - tri.v0;
            vector3d normal = edge1.crossproduct(edge2);
            normal.normalize();

        float push = carSphere.radius - dist + 0.01f;

        // repousse la voiture dans la direction du normal du bloc
        loc += normal * push;

        // corrige la vitesse pour éviter de retraverser
        velocity -= normal * velocity.dotproduct(normal);

        std::cout << "Collision bloc !" << std::endl;
    }
}
carSphere.center = loc;

  

}


		void car::setPosition(vector3d pos)
		{
		//	cs.center=pos;
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
 	vector3d forward;
    forward.x = cos(angle * M_PI / 180.0f);
    forward.z = sin(angle * M_PI / 180.0f);


	velocity.x += forward.x * s;
    velocity.z += forward.z * s;
	// projection dans l’axe avant et latéral
	float dotForward = velocity.x * forward.x + velocity.z * forward.z;
	vector3d forwardVel = forward * dotForward;
	vector3d sideVel = velocity - forwardVel;
	
	// friction latérale (glissement contrôlé)
	sideVel *= 0.6f;  // plus petit = adhérence forte, plus grand = drift
	
	velocity = forwardVel + sideVel;
	
    velocity *= 0.6f;
    
	// mise à jour position
	loc.x -= velocity.x*deltaTime;
	loc.z += velocity.z*deltaTime;
  
   }
   
   float car::getDeltaTime()
   {
   	return deltaTime;
   }
   
   void car::setDeltaTime(float t)
   {
   	deltaTime+=t;
   }
   
void car::control()
{
	const Uint8* state=SDL_GetKeyboardState(NULL);
			if(state[SDL_SCANCODE_M])
			{
				
					clavierAct++;
				
				}
					if(clavierAct>3)
					{
						clavierAct=0;
					}
				if(clavierAct==1)
				{
				
		if(state[SDL_SCANCODE_DOWN])
		{
			
	
			up=1;
			
		

			
			//moveCameraUp(0.0);
		}
			if(state[SDL_SCANCODE_DOWN]==false)
		{
			
	
			up=0;
			
		

			
			//moveCameraUp(0.0);
		}
		
			if(state[SDL_SCANCODE_UP])
		{
			
	
			down=1;
			
		

			
			//moveCameraUp(0.0);
		}
			if(state[SDL_SCANCODE_UP]==false)
		{
			
	
			down=0;
			
		

			
			//moveCameraUp(0.0);
		}
		
				if(state[SDL_SCANCODE_LEFT])
		{
			
	
			left=1;
			
		

			
			//moveCameraUp(0.0);
		}
			if(state[SDL_SCANCODE_LEFT]==false)
		{
			
	
			left=0;
			
		

			
			//moveCameraUp(0.0);
		}
		
				if(state[SDL_SCANCODE_RIGHT])
		{
			
	
			right=1;
			
		

			
			//moveCameraUp(0.0);
		}
			if(state[SDL_SCANCODE_RIGHT]==false)
		{
			
	
			right=0;
			
		

			
			//moveCameraUp(0.0);
		}
			if(state[SDL_SCANCODE_SPACE])
		{
			
		a_touch=1;
	}
		if(state[SDL_SCANCODE_SPACE]==false)
		{
			
		a_touch=0;
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

	float steerFactor = 0.4f + 0.6f * (fabs(speed) / maxSpeed); // min 0.4, max 1
	if(right) angle -= turnSpeed * steerFactor;
	if(left)  angle += turnSpeed * steerFactor;
	
	  // ?? pénalité réaliste en virage
	    if(left || right)
	{
	    float turnIntensity = fabs(speed / maxSpeed);
	    float penalty = 1.0f - (0.005f * turnIntensity); // plus faible
	    speed *= penalty;
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
 	return angle;
 }
float car::getMaxSpeed()
{
	return maxSpeed;
}
void car::setJoyTurnSpeed(bool a)
{
	joyTurn=a;
}

  
