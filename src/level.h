#ifndef LEVEL_H
#define LEVEL_H
#include<vector>
#include"collisionplane.h"
#include<iostream>
#include<GL/gl.h>
#include<GL/glu.h>
#include <C:/library/SDL-1.2.15/include/SDL/SDL.h>


class level
{
	unsigned int mesh;
	std::vector<collisionplane> cp;
	std::vector<vector3d> spawnpoints;
	std::string name;
	
	public:
level(const char* c,unsigned int map , std::vector<collisionplane>& cplane, std::vector<vector3d>& sp);
~level();
void update();
void show();
	std::vector<collisionplane>& getCollisionPlanes();
	std::string& getName();
	void change(const char* c,unsigned int map , std::vector<collisionplane>& cplane, std::vector<vector3d>& sp);
	std::vector<vector3d>& getSpawnPoints();
	
};
#endif
