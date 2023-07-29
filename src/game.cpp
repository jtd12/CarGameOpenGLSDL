#include"game.h"

game::game()
{

	 screenWidth=960;
	 screenHeight=540;
	GLfloat ambient[] = {0.15f,0.15f,0.15f,1.0f};
            GLfloat diffuse[] = {0.5f,0.5f,0.5f,1.0f};
            GLfloat light0_position [] = {0.0f, -1.0f, 0.0f, 0.0f};
            GLfloat specular_reflexion[] = {0.8f,0.8f,0.8f,1.0f};
            GLubyte shiny_obj = 128;
		SDL_Init(SDL_INIT_EVERYTHING);
		TTF_Init();
		   SDL_WM_SetCaption("Car Game OpenGL 2.0!", NULL);
		if(SDL_INIT_JOYSTICK<0)
		{
			printf("impossible joystick!");
		}
		 if( SDL_NumJoysticks() < 1 )
        {
            printf( "Warning: No joysticks connected!\n" );
        }
		 if (SDL_Init(SDL_INIT_AUDIO) < 0)
      	{
      		printf("son impossible!");
		  }
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }
         screen=SDL_SetVideoMode( screenWidth,  screenHeight,32,SDL_OPENGL|SDL_RESIZABLE);
     	music=Mix_LoadMUS("data/audio/background.mp3");
     	audio();
        glClearColor(1.0,1.0,1.0,1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(65,960.0/540.0,0.1,35000.0);
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_COLOR_MATERIAL);
       
    
     
       
      //	initskybox();
      	std::vector<collisionplane> mapcp;
     
      	std::vector<vector3d> mapsp;
      	mapsp.push_back(vector3d(0.1,0.2,0.1));
      	
       unsigned int map=obj.load("data/decor/map.obj",&mapcp);
    unsigned int map2=obj.load("data/decor/map2.obj",&mapcp);
     unsigned int map3=obj.load("data/decor/map3.obj",&mapcp);
          unsigned int map4=obj.load("data/decor/map4.obj",&mapcp);
            unsigned int map5=obj.load("data/decor/map5.obj",&mapcp);
         unsigned int map6=obj.load("data/decor/collision_01.obj",&mapcp);
       
   
        unsigned int map11=obj.load("data/decor/sky.obj",&mapcp); 
        
      levels.push_back(new level("name",map,mapcp,mapsp));
        levels.push_back(new level("name",map2,mapcp,mapsp));
               levels.push_back(new level("name",map3,mapcp,mapsp));
                levels.push_back(new level("name",map4,mapcp,mapsp));
                 levels.push_back(new level("name",map5,mapcp,mapsp));
                    levels.push_back(new level("name",map6,mapcp,mapsp));
  	
                   levels.push_back(new level("name",map11,mapcp,mapsp));      
					 
                unsigned int mesh=obj.load("",&mapcp);
               	vehicule.push_back(new car(mesh,"voiture",collisionsphere(vector3d(-350,50,65),3.2),0.02,0.0,0.7));
      //weapons.push_back(new weapon())
    playerCam_=new playerCam("player1",collisionsphere(vector3d(-350,60,75),30.0),0.02,3.0,0.2);
    joystick=SDL_JoystickOpen(0);
  
 
 //std::vector<unsigned int> anim;
 //obj.loadAnimation(anim, "data/object/carsAI",100);
    //weapons.push_back(new weapon(anim,anim[0],1,16,19,vector3d(0,0,0),vector3d(0,0,0),vector3d(0,0,0),vector3d(0,0,0),100,1000,10,30,300,20,"weapon_anim",1));
           //loadAnimation(anim, "C:/Users/jtd/Documents/jeu fps/data/weapon_anim",38);
          // weapons.push_back(new weapon(anim,anim[0],1,16,19,vector3d(0,0,0),vector3d(0,0,0),vector3d(0,0,0),vector3d(0,0,0),100,1000,10,30,300,20,"C:/Users/jtd/Documents/jeu fps/data/weapon_anim/weapon_000001.obj",1));



  //  cube=loadObject("test.obj");
       
       
      
}

game::~game()
{
	for(int i=0;i<levels.size();i++)
	delete levels[i];
	delete playerCam_;
		for(int i=0;i<vehicule.size();i++)
	delete vehicule[i];
delete screen;
Mix_FreeMusic(music);
Mix_CloseAudio();
SDL_JoystickClose (joystick);
	SDL_Quit();
//	killskybox();
}
void game::start()
{
	bool running=true;
	Uint32 start;
   
     	joystick=NULL;
        SDL_JoystickEventState(SDL_ENABLE);
        
        while(running)
        {
    
                start=SDL_GetTicks();
                while(SDL_PollEvent(&event))
                {
                	  if(event.type == SDL_VIDEORESIZE)
                {
                    screenWidth  = event.resize.w;
                    screenHeight = event.resize.h;

                    glViewport(0, 0, screenWidth, screenHeight);
                 
                    
                
                }
                        switch(event.type)
                        {
                        	case SDL_JOYAXISMOTION:
                        	
                        
							
                        				if( event.jaxis.which == 0 )
						{	
					
					
				
							
				  if(event.jaxis.axis==2)
									{
						
                        		if(event.jaxis.value>8000 )
									{
							
								
						vehicule[0]->setUP(1);
						
						
							
						}
								else if(event.jaxis.value<-8000 )
                        		{
							
                       	
	
									
							vehicule[0]->setDOWN(1);
								
							
						}	
					
					else
					{
							vehicule[0]->setUP(0);
									
							vehicule[0]->setDOWN(0);
					}
			}
						 		
				 if(event.jaxis.axis==0)
						{
									if(event.jaxis.value>8000 || event.jaxis.value<-8000)
									{
									if(vehicule[0]->getSpeed()!=0)
									 vehicule[0]->setjoy((event.jaxis.value*-0.0002f)*-vehicule[0]->getSpeed()/vehicule[0]->getMaxSpeed());
									 vehicule[0]->setTurn(1);
						}
								else
								{
								vehicule[0]->setTurn(0);
							
							}
								
							
				//vehicule[0]->angle-=(event.jaxis.value*0.0005f)*-vehicule[0]->speed/vehicule[0]->maxSpeed;
			
				 }
				 
	
					
					
				 if(event.jaxis.axis==4)
									{
						
                        		if(event.jaxis.value>8000 )
                        		{
							
                        		
								
							playerCam_->setAroundTouch(1);
						
							
						}
					
								else if(event.jaxis.value<-8000 )
                        		{
							
                       	
									playerCam_->setAroundTouch2(1);
								
							
						}		
			
			
						else
						{
									playerCam_->setAroundTouch(0);
									
								playerCam_->setAroundTouch2(0);
							
					
										
						}
						
				 }
					
						 if(event.jaxis.axis==3)
									{
						
                        		if(event.jaxis.value>8000 )
                        		{
							
                        		
								
							playerCam_->setAroundTouch3(1);
						
							
						}
					
								else if(event.jaxis.value<-8000 )
                        		{
							
                       	
									playerCam_->setAroundTouch4(1);
								
							
						}		
			
			
						else
						{
									playerCam_->setAroundTouch3(0);
									
								playerCam_->setAroundTouch4(0);
							
					
										
						}
						
					
					
				}
		 }
				
								break;
							
							
							case SDL_JOYBUTTONDOWN:
								if(event.jbutton.button==0)
								{
									vehicule[0]->setA(1);
								}
								else
								{
										vehicule[0]->setA(0);
								}
								break;
							
                                case SDL_QUIT:
                                        running=false;
                                        break;
                                case SDL_MOUSEBUTTONDOWN:
                                       
                                       playerCam_->cam.mouseIn(true);
                                       SDL_ShowCursor(SDL_DISABLE);
                                        break;
                                case SDL_KEYDOWN:
                                        if(event.key.keysym.sym==SDLK_p)
                                        {
                                            
                                        playerCam_->cam.mouseIn(false);
                                       SDL_ShowCursor(SDL_ENABLE);
                                                break;
                                        }
                                        if(event.key.keysym.sym==SDLK_ESCAPE)
                                        {
                                                running=false;
                                                break;
                                        }      
                                     
                                 
										switch(event.key.keysym.sym)
										{
										
											case SDLK_UP:
										
												break;
												case SDLK_DOWN:
											
													break;
														case SDLK_RIGHT:
													
													break;
														case SDLK_LEFT:
													
													break;
													case SDLK_SPACE:
																vehicule[0]->setA(1);
														//playerCam_->setJump();
														break;
													case SDLK_LSHIFT:
														playerCam_->setSprint();
														break;
										   } 
										   
										   break; 
										   
										   case SDL_KEYUP:
										   	switch(event.key.keysym.sym)
										   	{
										   		case SDLK_UP:
										   
										   			break;
										   				case SDLK_DOWN:
										
										   			break;
										   			case SDLK_RIGHT:
											
													break;
														case SDLK_LEFT:
												
													break;
														case SDLK_SPACE:
																vehicule[0]->setA(0);
														//playerCam_->setJump();
														break;
														case SDLK_LSHIFT:
														playerCam_->stopSprint();
														break;
										   		
											   }                   
                    }
                }
            
		
				
                if(vehicule[0]->getTurn())
               	vehicule[0]->setJoyTurnSpeed(1);
               	
               	else
               		vehicule[0]->setJoyTurnSpeed(0);
                update();
                show();
            
                SDL_GL_SwapBuffers();
                
                /*if(collision::spheresphere(cameraPos,2.0,vector(0,0,0),1.0))
                        std::cout << "collision\n";
                collision::sphereplane(cameraPos,vector(0,0,1),p1,p2,p3,p4,2.0);
                collision::sphereplane(cameraPos,vector(0,0.9701425,0.242535625),p5,p6,p7,p8,2.0);
                
          */
				
                if(1000/30>(SDL_GetTicks()-start))
                        SDL_Delay(1000/30-(SDL_GetTicks()-start));
        }
}

void game::update()
{

     	playerCam_->update(levels[0]->getCollisionPlanes());
		playerCam_->orbit();
      	for(int i=0;i<vehicule.size();i++)
      	  vehicule[i]->update(levels[0]->getCollisionPlanes());
      	for(int i=0;i<vehicule.size();i++)
      	  vehicule[i]->control();
      for(int i=0;i<levels.size();i++)
      
      	levels[i]->update();
	

}

void game::lighting()
{
	GLfloat ambient[] = {0.3f,0.2f,0.2f,0.9f};
            GLfloat diffuse[] = {1.0f,1.0f,1.0f,1.0f};
            GLfloat light0_position [] = {0.0f, 5.0f, 1000.0f, 10.0f};
            GLfloat specular_reflexion[] = {0.9f,0.9f,0.9f,1.0f};
            GLubyte shiny_obj = 128;

                        //positionnement de la lumière avec les différents paramètres
            glEnable(GL_LIGHTING);
            glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
            glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
            glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
            glEnable(GL_LIGHT0);

                         //spécification de la réflexion sur les matériaux
            glEnable(GL_COLOR_MATERIAL);
            glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
            glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
            glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular_reflexion);
            glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,shiny_obj);
          
    
}
void game::RenderText(std::string message, SDL_Color color, int x, int y,float x2,float y2, int size) {
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  gluOrtho2D(0, 960, 0, 540); // m_Width and m_Height is the resolution of window
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  glDisable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  TTF_Font * font = TTF_OpenFont("data/angelina.ttf", size);
  const char*c=message.c_str(); 
  SDL_Surface * sFont = TTF_RenderText_Blended(font, c, color);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sFont->pixels);
	glTranslated(x2,y2,0);
  glBegin(GL_QUADS);
  {
    glTexCoord2f(0,1); glVertex2f(-x, -y);
    glTexCoord2f(1,1); glVertex2f(x + sFont->w, -y);
    glTexCoord2f(1,0); glVertex2f(x + sFont->w, y + sFont->h);
    glTexCoord2f(0,0); glVertex2f(-x, y + sFont->h);
    
    /*
    glTexCoord2i(0,1);glVertex3i(-1,-1,-1);
glTexCoord2i(1,1);glVertex3i(+1,-1,-1);
glTexCoord2i(1,0);glVertex3i(+1,+1,-1); 
glTexCoord2i(0,0);glVertex3i(-1,+1,-1);
*/
  }
  glEnd();

  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
  glDeleteTextures(1, &texture);
  TTF_CloseFont(font);
  SDL_FreeSurface(sFont);
}
std::string game::float2str(float x) {
    // converts int to string
    std::stringstream ss;
    ss << x;
    return ss.str( );
}

void game::audio()
{
	 
   	Mix_PlayMusic(music,-1);
    

}

void game::show()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glLoadIdentity();
      

      // playerCam_->cam.setLocation(vector3d(vehicule[0]->getLocation().x+5*cos(vehicule[0]->getRotation().x*M_PI/180),vehicule[0]->getLocation().y+12,vehicule[0]->getLocation().z+5*sin(vehicule[0]->getRotation().z*M_PI/180)));
		//Control(0.2,0.2,mousein);
		//(sin(car1->rot*3.14159265359/180.0)*30)
		float camX=vehicule[0]->getLocation().x+(cos(vehicule[0]->getRotation().y*3.14159265359/180.0)*-10);
		float camY=vehicule[0]->getLocation().y+5;
		float camZ=vehicule[0]->getLocation().z+(sin(vehicule[0]->getRotation().y*3.14159265359/180.0)*10);
		  
		float targetX=vehicule[0]->getLocation().x;
		float targetY=vehicule[0]->getLocation().y+4;
		float targetZ=vehicule[0]->getLocation().z;
		  playerCam_->cam.Control();
		 // playerCam_->cam.UpdateCamera();
		
        gluLookAt(camX,camY,camZ,targetX,targetY,targetZ,0,1,0);
        //player1->cam.Control();
        //drawSkybox(50.0);
 lighting();
//playerCam_->cam.UpdateCamera();

           for(int i=0;i<levels.size()-1;i++)
		
      	    levels[i]->show();
   
      	for(int i=0;i<vehicule.size();i++)
      	  vehicule[i]->show();
      
      glDisable(GL_LIGHTING);
      for(int i=6;i<levels.size();i++)
       levels[i]->show();
          
      	  SDL_Color color = {255, 0, 0, 0}; // Red
      	  
      	  SDL_Color color2 = {255, 50, 100, 0}; // Red
	glPushMatrix();
  RenderText("vitesse:"+float2str(vehicule[0]->getSpeed()*-20.0f), color, -1.0, 0.9,0.1,0.5, 50);
RenderText("angle:"+float2str(vehicule[0]->getJoy()), color2, 1.0, 0.2,0.1,0.1, 50);
	glPopMatrix();
      	
   //	player1->cam.loc.x=car1->loc.x+2;
        //UpdateCamera();
}

