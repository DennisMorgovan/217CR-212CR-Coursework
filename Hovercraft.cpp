#include "Hovercraft.h"

#define PI 3.14159265

Hovercraft::Hovercraft(glm::vec3 position, char *fname, GLuint uniqueID) : GameObject(position)
{
	hovercraft.loadModelQuads(fname, uniqueID);
}


Hovercraft::~Hovercraft()
{
}

void Hovercraft::start(char *fname, GLuint uniqueID)
{
	hovercraft.loadModelQuads(fname, uniqueID);
}

void Hovercraft::update(int deltaTime)
{
}

void Hovercraft::draw()
{
	glPushMatrix();
		glTranslatef(position.x, 0.0, position.z);
		glColor3f(1.0, 0.23, 0.27);
		glScalef(0.5, 0.5, 0.5);
		glRotatef(angle, 0, 1, 0);
	
		glPushMatrix();
			glRotatef(180, 0, 1, 0); //Rotates the hovercraft into the correct position at star
			hovercraft.drawObjQuads();
		glPopMatrix();
	glPopMatrix();
}

void Hovercraft::movement(int key)
{
	//Captures left, right, up and down key inputs and adjusts the angles and x and z coordinates appropriately
	if (key == GLUT_KEY_LEFT)
		angle = angle + 5.0; //Reason for the angle moving by +5 degrees when turning left is because OpenGL keeps track of angles counter-clockwise
	if (key == GLUT_KEY_RIGHT)
		angle = angle - 5.0;
	if (key == GLUT_KEY_UP)
	{
		position.x = position.x - sin(angle * PI / 180.0);
		position.z = position.z - cos(angle * PI / 180.0);
	}
	if (key == GLUT_KEY_DOWN)
	{
		position.x = position.x + sin(angle * PI / 180.0);
		position.z = position.z + cos(angle * PI / 180.0);
	}

	// Angle correction.
	if (angle > 360.0)
		angle -= 360.0;
	if (angle < 0.0)
		angle += 360.0;
}