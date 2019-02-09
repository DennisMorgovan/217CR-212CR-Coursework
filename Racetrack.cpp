#include "Racetrack.h"



Racetrack::Racetrack(glm::vec3 position, char *fname, GLuint uniqueID) : GameObject(position)
{
	racetrack.loadModel(fname, uniqueID);
}


Racetrack::~Racetrack()
{
}

void Racetrack::start(char *fname, GLuint uniqueID)
{
	racetrack.loadModel(fname, uniqueID);
}

void Racetrack::update(int deltaTime)
{
}

void Racetrack::draw()
{
	//Racetrack transform
	glPushMatrix();
		glTranslatef(0, 0, 0);
		glColor3f(1.0, 0.23, 0.27);
		glScalef(1, 1, 1);
		glRotatef(racetrackrot, 0, 1, 0);

		//Creates racetrack
		racetrack.drawObj();
	glPopMatrix();

	//Racetrack rotation; used for displaying the model
	//racetrackrot = racetrackrot + 0.6;
	//if (racetrackrot > 360)
	//	racetrackrot = racetrackrot - 360;
	
}