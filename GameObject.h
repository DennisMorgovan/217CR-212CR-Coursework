#pragma once
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#  include <glm/glm.hpp> 
#pragma comment(lib, "glew32.lib") 
#endif 

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

	/* Every GameObject must implement the following pure virtual function or otherwise cause a compile error.*/
	virtual void start() = 0; ///<Pure virtual start function, run once when the engine starts.  Must override in inherited classes.
	virtual void update(int deltaTime) = 0; ///<Pure virtual update function, run periodicity to update the game state. Must override in inherited classes.

	GameObject(glm::vec3 position);
	~GameObject();
};