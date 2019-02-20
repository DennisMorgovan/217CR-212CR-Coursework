#include "Grassfield.h"

Grassfield::Grassfield(glm::vec3 position, char * fname, GLuint uniqueID) : GameObject(position)
{
	Grassfield::collider = new CubeCollider(&this->position, 1500, 1, 1500, 1);
	this->collider->objectType = 3;

	grass.loadModelQuads(fname, uniqueID);
}

Grassfield::~Grassfield()
{
}

void Grassfield::start(char * fname, GLuint uniqueID)
{
}

void Grassfield::update(int deltaTime)
{
}

void Grassfield::draw()
{
	glPushMatrix();
		glColor3f(0, 1, 0);
		glTranslatef(0, 0, 0);
		grass.drawObjQuads();
	glPopMatrix();

	this->collider->Draw();
}
