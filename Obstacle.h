#pragma once
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#  include <glm/glm.hpp> 
#pragma comment(lib, "glew32.lib") 
#endif 

//Class for game obstacles
class Obstacle
{
private:
	glm::vec3 position; //Object pos
	unsigned int base;
	glm::vec3 colour; //Object colour
public:
	Obstacle(glm::vec3 position, glm::vec3 objColour);
	~Obstacle();

	void draw();
	void start();
	void update(int deltaTime);
	unsigned int setupDrawing(unsigned int listBase);
};

