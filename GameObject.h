#pragma once
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#  include <glm/glm.hpp> 
#pragma comment(lib, "glew32.lib") 
#endif 

#include "Collider.h"

#include<map>
# include <glm/glm.hpp> 

//#include "Collider.h"

class GameObject
{
private:
	int faceMode; //In what way the object is created (i.e. using quad faces = 1 or triangled faces = 0)
protected: //Means this cannot be accessed by outside, but can be accessed by inheriting classes
	unsigned int base; 
public:
	glm::vec3 position;
	virtual unsigned int setupDrawing(unsigned int listBase);
	virtual void draw(); ///Function to perform this object's part of the redraw work. The default version in GameObject will put the object in the right place and redraw it. This can be overridden.

	Collider* collider = NULL;  ///<Pointer to a collider for the game object. Initially NULL to indicate that we do not want to calculate collisions.

	//Stores keys as pairs of key and state (true = pressed, false = released)
	static std::map <int, bool> specialKeys;	
	static std::map <char, bool> keys;

	static bool debugMode;
	bool active = true;

	glm::vec3 heading = glm::vec3(0.0, 0.0, -1.0);  ///<Current heading (direction) the GameObject is facing.

	/* Every GameObject must implement the following pure virtual function or otherwise cause a compile error.*/
	virtual void start() = 0; ///<Pure virtual start function, run once when the engine starts.  Must override in inherited classes.
	virtual void update(int deltaTime) = 0; ///<Pure virtual update function, run periodicity to update the game state. Must override in inherited classes.

	virtual void collides(Collider* other); ///<Virtual function to notify this game object that a collision has happened can be overridden (optional).

	GameObject(glm::vec3 position);
	~GameObject();
};