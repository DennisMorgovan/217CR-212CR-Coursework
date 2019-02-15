#pragma once
/* OPENGL_INCLUDES */
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib") 
#endif 

#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <vector>

#include "Hovercraft.h"
#include "Reader.h"
#include "Obstacle.h"
#include "Racetrack.h"
#include "Camera.h"
#include "Lighting.h"
#include "GameObject.h"


class GameEngine
{
private:
	static std::vector<GameObject*> gameobjects; ///<Vector of (pointers to) game objects: all the objects in the game.

public:
	GameEngine();
	~GameEngine();
};

