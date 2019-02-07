#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#  include <glm/glm.hpp> 
#pragma comment(lib, "glew32.lib") 
#endif 
#include "Obstacle.h"


Obstacle::Obstacle(glm::vec3 position, glm::vec3 objColour) : GameObject(position)
{
	this->colour = objColour;
}

Obstacle::~Obstacle()
{
}

void Obstacle::draw()
{
	glPushMatrix();
		glTranslatef(this->position.x, this->position.y, this->position.z);
		glCallList(this->base);
	glPopMatrix();
}

void Obstacle::start() {
}

void Obstacle::update(int deltaTime) {
}

unsigned int  Obstacle::setupDrawing(unsigned int listBase) {
	this->base = ++listBase;

	glNewList(this->base, GL_COMPILE);
		glPushMatrix();
			glRotatef(-45, 1, 0, 0);
			glColor3f(this->colour.x, this->colour.y, this->colour.z);
			glutSolidSphere(1.0, 40, 40);
		glPopMatrix();
	glEndList();
	return this->base;
}