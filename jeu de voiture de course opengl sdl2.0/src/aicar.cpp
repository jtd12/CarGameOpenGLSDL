#include"aicar.h"

carAI::carAI(std::vector<unsigned int>& anim,float sp,collisionsphere css)
 {
 	frames=anim;
	cs=css;
	speed=sp;


 }
 carAI::~carAI()
 {
 }
 void carAI::update(std::vector<collisionplane>& collplane)
 {

			vector3d newPos(cs.center);
			newPos.y-=0.5f;
	 		newPos+=direction*speed;
	 	/*	rotation.z=std::acos(-direction.x);
	 				if(direction.z>0)
	 				{
	 					rotation.z=-rotation.z;
					 }
					 */

	 		for(int i=0;i<collplane.size();i++)
				collision::sphereplane(newPos,collplane[i].normal,collplane[i].p[0],collplane[i].p[1],collplane[i].p[2],collplane[i].p[3],cs.r);
	 			
	 		setLocation(newPos);
	 		
					 curFrame+=0.08f;
					 if( curFrame>=100)
					 {
					 	curFrame=0;
					 }


 }
 void carAI::show()
 {
 	glPushMatrix();
		glTranslatef(cs.center.x,cs.center.y,cs.center.z);

	 	glRotatef(-rotation.x*(180/pi),1,0,0);
	 	glRotatef(-rotation.y*(180/pi),0,1,0);
	 	glRotatef(-rotation.z*(180/pi),0,0,1);
	 
	 	glCallList(frames[curFrame]);
	 	glPopMatrix();

 }
 collisionsphere * carAI::getCollisionSphere()
		{
				return &cs;
		}
		void carAI::setLocation(vector3d newLoc)
		{
			cs.center=newLoc;
		}

