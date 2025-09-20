#include"game.h"

game::game()
{
	/*
	Sphere car;
car.center = vector3d(0,2,0); // position
car.radius = 1.0f;

// Mesh chargé depuis ton .obj
std::vector<Triangle> mesh = loadObjAsTriangles("decor.obj");

// Déplacement tentative
vector3d move(0.1f, -0.2f, 0.0f);
car.center = car.center + move;

// Vérif collision
if (collideSphereMesh(car, mesh)) {
    // car.center a été corrigé automatiquement
    // tu peux aussi ajuster la vitesse (annuler la composante normale)
}
 */ 
		initSDL();


		
  

     	//audio();
    
   	
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
      	
       unsigned int map=obj.load("data/decor/map.obj");
    unsigned int map2=obj.load("data/decor/map2.obj");
     unsigned int map3=obj.load("data/decor/map3.obj");
          unsigned int map4=obj.load("data/decor/map4.obj");
            unsigned int map5=obj.load("data/decor/map5.obj");
            unsigned int map6=obj.load("data/decor/sky.obj");
 			unsigned int map7=obj.load("data/decor/map6.obj");
 			
      levels.push_back(new level("name",map,mapcp,mapsp));
        levels.push_back(new level("name",map2,mapcp,mapsp));
               levels.push_back(new level("name",map3,mapcp,mapsp));
                levels.push_back(new level("name",map4,mapcp,mapsp));
                 levels.push_back(new level("name",map5,mapcp,mapsp));
                levels.push_back(new level("name",map6,mapcp,mapsp));
                levels.push_back(new level("name",map7,mapcp,mapsp));
				terrain=new objloader();
      			terrain->load("data/decor/collision_01.obj");
      			terrain2=new objloader();
      			terrain2->load("data/decor/collision_02.obj");


					 
                unsigned int mesh=obj.load("data/car.obj");
               	vehicule.push_back(new car(mesh,"voiture",0.02,0.0,0.7,terrain));
      //weapons.push_back(new weapon())
    playerCam_=new playerCam("player1",0.02,3.0,0.2);
    joystick=SDL_JoystickOpen(0);
    music=Mix_LoadMUS("data/audio/background.mp3");
    audio();
  captureVideo_=new captureVideo(screenWidth, screenHeight, 60, "output.mp4");
 frameIndex = 0;
 
 //std::vector<unsigned int> anim;
 //obj.loadAnimation(anim, "data/object/carsAI",100);
    //weapons.push_back(new weapon(anim,anim[0],1,16,19,vector3d(0,0,0),vector3d(0,0,0),vector3d(0,0,0),vector3d(0,0,0),100,1000,10,30,300,20,"weapon_anim",1));
           //loadAnimation(anim, "C:/Users/jtd/Documents/jeu fps/data/weapon_anim",38);
          // weapons.push_back(new weapon(anim,anim[0],1,16,19,vector3d(0,0,0),vector3d(0,0,0),vector3d(0,0,0),vector3d(0,0,0),100,1000,10,30,300,20,"C:/Users/jtd/Documents/jeu fps/data/weapon_anim/weapon_000001.obj",1));



  //  cube=loadObject("test.obj");
       
       
      
}


bool game::initSDL()
{
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	
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
		  
		  TTF_Init();
		  
		  
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }
		
	 if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);


   
   	pWindow=SDL_CreateWindow("car game SDL_OpenGL",100,100,screenWidth, screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if(!pWindow)
    {
    	fprintf(stderr,"error!", SDL_GetError());
	}
  
    
    SDL_GLContext context;
    context=SDL_GL_CreateContext(pWindow);
    if(!context)
    {
    	fprintf(stderr,"error!", SDL_GetError());
	}
	
	gladLoadGLLoader(SDL_GL_GetProcAddress);
	
}

game::~game()
{
	for(int i=0;i<levels.size();i++)
	delete levels[i];
	delete playerCam_;
		for(int i=0;i<vehicule.size();i++)
	delete vehicule[i];
	delete captureVideo_;
delete screen;
Mix_FreeMusic(music);
Mix_CloseAudio();
SDL_JoystickClose (joystick);
SDL_Quit();

//	killskybox();
}

void game::resizeWindow(int windowWidth, int windowHeight) {
   // logFileStderr("MESSAGE: Window width, height ... %d, %d\n", windowWidth, windowHeight);
    //m_camera->resizeWindow(windowWidth, windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);
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
    glViewport(0,0,screenWidth,screenHeight);
              
                while(SDL_PollEvent(&event))
                {
               
                	  switch(event.type)
                        {
                	
                     case SDL_WINDOWEVENT:

        if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
            //logFileStderr("MESSAGE:Resizing window...\n");
            		screenWidth  = event.window.data1;
                    screenHeight = event.window.data2;

                    glViewport(0, 0, screenWidth, screenHeight);
        }
        break;
                    	case SDL_JOYAXISMOTION:
							
                        if( event.jaxis.which == 0 )
						{	
				 if (event.jaxis.axis == 1) { // ton axe combiné (à vérifier avec printf)
		        int val = event.jaxis.value;
		
		        // Zone morte centrale
		        if (val > -5000 && val < 5000) {
		            vehicule[0]->setUP(0);
		            vehicule[0]->setDOWN(0);
		        }
		        // Accélérateur
		        else if (val > -5000) {
		            vehicule[0]->setUP(1);
		            vehicule[0]->setDOWN(0);
		        }
		        // Frein
		        else if (val < 5000) {
		            vehicule[0]->setDOWN(1);
		            vehicule[0]->setUP(0);
		        }
		    }
		    
		      if (event.jaxis.axis == 0) { // axe volant gauche/droite (à vérifier avec printf)
		        int val = event.jaxis.value;
		
		        // Deadzone pour éviter de déclencher en ligne droite
		        if (val < -5000) { 
		            vehicule[0]->setLEFT(1);
		            vehicule[0]->setRIGHT(0);
		        }
		        else if (val > 5000) {
		            vehicule[0]->setRIGHT(1);
		            vehicule[0]->setLEFT(0);
		        }
		        else {
		            vehicule[0]->setLEFT(0);
		            vehicule[0]->setRIGHT(0);
		        }
		    }
		    
		    if(event.jaxis.axis == 2)
		    {
		    	 int val = event.jaxis.value;
		    	 
		    	 if (val < -5000) { 
		            playerCam_->cam.setYaw(true);
		            playerCam_->cam.setYaw2(false);
		        }
		        else if (val >5000) { 
		            playerCam_->cam.setYaw(false);
		            playerCam_->cam.setYaw2(true);
		        }
		        else
		        {
		        playerCam_->cam.setYaw(false);
		        playerCam_->cam.setYaw2(false);
				}
		    
			}
			
			  if(event.jaxis.axis == 3)
		    {
		    	 int val = event.jaxis.value;
		    	 
		    	 if (val < -5000) { 
		            playerCam_->cam.setPitch(true);
		            playerCam_->cam.setPitch2(false);
		        }
		        else if (val >5000) { 
		            playerCam_->cam.setPitch(false);
		            playerCam_->cam.setPitch2(true);
		        }
		        else
		        {
		        playerCam_->cam.setPitch(false);
		        playerCam_->cam.setPitch2(false);
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
													case SDL_SCANCODE_SPACE:
															//	vehicule[0]->setA(1);
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
														case SDL_SCANCODE_SPACE:
															//	vehicule[0]->setA(0);
														//playerCam_->setJump();
														break;
														case SDLK_LSHIFT:
														playerCam_->stopSprint();
														break;
										   		
											   }                
	

                   }
			
		}
		
			playerCam_->cam.setPitch(1.5f);
			playerCam_->cam.setYaw(1.5f);
		
	 		if(vehicule[0]->getTurn())
               	vehicule[0]->setJoyTurnSpeed(1);
               	
               	else
               		vehicule[0]->setJoyTurnSpeed(0);
     
                update();
                show();
       
              	SDL_GL_SwapWindow(pWindow);


                
                /*if(collision::spheresphere(cameraPos,2.0,vector(0,0,0),1.0))
                        std::cout << "collision\n";
                collision::sphereplane(cameraPos,vector(0,0,1),p1,p2,p3,p4,2.0);
                collision::sphereplane(cameraPos,vector(0,0.9701425,0.242535625),p5,p6,p7,p8,2.0);
                
          */
				
          if(1000/30>(SDL_GetTicks()-start))
                        SDL_Delay(1000/30-(SDL_GetTicks()-start));

        }
      SDL_DestroyWindow(pWindow);
}


void game::update()
{
	

		captureVideo_->captureFrame();

     //	playerCam_->update(levels[5]->getCollisionPlanes());
		//playerCam_->orbit();
      	for(int i=0;i<vehicule.size();i++)
      	  vehicule[i]->update(terrain->collisionMesh,terrain);
      	
      	for(int i=0;i<vehicule.size();i++)
      	  vehicule[i]->update2(terrain2->collisionMesh);
      	  
      	for(int i=0;i<vehicule.size();i++)
      	  vehicule[i]->control();
      for(int i=0;i<levels.size();i++)
      
      	levels[i]->update();
	

}

void game::lighting()
{
	GLfloat ambient[] = {0.9f,0.5f,0.8f,0.9f};
            GLfloat diffuse[] = {0.2f,0.0f,1.0f,1.0f};
            GLfloat light0_position [] = {0.0f, 500.0f, 100.0f, 10.0f};
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
  //SDL_Surface * sFont = TTF_RenderText_Blended(font, c, color);
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
    //TTF_CloseFont(font);

 
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


           for(int i=0;i<levels.size();i++)
		
      	    levels[i]->show();
      	    
   	for(int i=0;i<vehicule.size();i++)
      	  vehicule[i]->show();
      
   
          
      	  SDL_Color color = {255, 0, 0, 0}; // Red
      	  
      	  SDL_Color color2 = {255, 50, 100, 0}; // Red
		glPushMatrix();
	  	RenderText("vitesse:"+float2str(vehicule[0]->getSpeed()*-50.0f), color, -1.0, 0.9,0.1,0.5, 50);
		RenderText("angle:"+float2str(vehicule[0]->getJoy()), color2, 1.0, 0.2,0.1,0.1, 50);
		glPopMatrix();
	
	
      	
   //	player1->cam.loc.x=car1->loc.x+2;
        //UpdateCamera();
}

