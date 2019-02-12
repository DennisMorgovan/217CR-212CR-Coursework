#include "Hovercraft.h"

#define PI 3.14159265

Hovercraft::Hovercraft(glm::vec3 position, char *fnameBody, char *fnamePropeller, GLuint uniqueID) : GameObject(position)
{
	hovercraft.loadModelQuads(fnameBody, uniqueID);
	hovercraftPropeller.loadModelQuads(fnamePropeller, uniqueID);
	propellerRotForward = false;
	propellerRotBackward = false;
	propellerAngle = 0.0f;
}

Hovercraft::~Hovercraft()
{
}

void Hovercraft::start(char *fnameBody,char *fnamePropeller, GLuint uniqueID)
{
	hovercraft.loadModelQuads(fnameBody, uniqueID);
	hovercraftPropeller.loadModelQuads(fnamePropeller, uniqueID);
}

void Hovercraft::update(int deltaTime)
{
	float moveStep = MOVE_SPEED * (deltaTime / 1000.0); //movement speed in units per second * deltaTime in sec = moveStep
	float turningSpeed = TURNING_SPEED * (deltaTime / 1000.0); //turning speed (degrees/sec) * deltaTime in sec = turning speed over delta time

	if (specialKeys[GLUT_KEY_DOWN]) {
		this->position -= this->heading * moveStep;
		propellerRotBackward = true;
		propellerRotForward = false;
		propellerAngle += 5.0f;
	}

	if (specialKeys[GLUT_KEY_UP]) {
		this->position += this->heading * moveStep;
		propellerRotForward = true;
		propellerRotBackward = false;
		propellerAngle += 5.0f;
	}

	if (specialKeys[GLUT_KEY_PAGE_UP]) {
		this->pitchAngle += turningSpeed; //in degrees not radians
	}

	if (specialKeys[GLUT_KEY_PAGE_DOWN]) {
		this->pitchAngle -= turningSpeed; //in degrees not radians
	}

	if (specialKeys[GLUT_KEY_LEFT]) {
		this->rotationAngle += turningSpeed; //in degrees not radians
	}

	if (specialKeys[GLUT_KEY_RIGHT]) {
		this->rotationAngle -= turningSpeed; //in degrees not radians
	}

	this->heading = glm::rotate(this->startingHeading, glm::radians(rotationAngle), glm::vec3(0.0, 1.0, 0.0));
	this->heading = glm::rotate(this->heading, glm::radians(pitchAngle), glm::vec3(0.0, 0.0, 1.0));

	if (propellerAngle > 360.0)
		propellerAngle -= 360.0;
}

void Hovercraft::draw()
{
	float matAmb1[] = { 0.0, 0.0, 1.0, 1.0 };
	float matDif1[] = { 0.0, 0.0, 1.0, 1.0 };

	glPushMatrix();
		glTranslatef(position.x, position.y, position.z); //Updates the position of the hovercraft
		glColor3f(0.6, 1, 0.8); //Hovercraft colour
		glScalef(0.5, 0.5, 0.5); 

		glRotatef(pitchAngle, 0, 0, 1);
		glRotatef(rotationAngle, 0, 1, 0); //Rotates the hovercraft when correct keys are inputted
	
		glPushMatrix();
			glRotatef(180, 0, 1, 0); //Rotates the hovercraft into the correct position at start
			glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb1);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif1);
			hovercraft.drawObjQuads();

			glPushMatrix();
				if (propellerRotForward == true) //Rotate the propeller only if the right keys are pressed
				{
					//Rotate around the propeller's center
					glTranslatef(0, 3.5, 0); //Move propeller back to where it started
					glRotatef(propellerAngle, 0, 0, 1); //Apply rotation via the angle about the z axis
					glTranslatef(0, -3.5, 0); //Move propeller to origin
				}
				else if (propellerRotBackward == true)
				{
					//Rotate around the propeller's center
					glTranslatef(0, 3.5, 0); //Move propeller back to where it started
					glRotatef(-propellerAngle, 0, 0, 1); //Apply rotation via the angle about the z axis
					glTranslatef(0, -3.5, 0); //Move propeller to origin
				}
				hovercraftPropeller.drawObjQuads(); //Draws the propeller
			glPopMatrix();

		glPopMatrix();
	glPopMatrix();


}

void Hovercraft::movement(int key)
{
	//Captures left, right, up and down key inputs and adjusts the angles and x and z coordinates appropriately
	//if (key == GLUT_KEY_LEFT)
	//	angle = angle + 5.0; //Reason for the angle moving by +5 degrees when turning left is because OpenGL keeps track of angles counter-clockwise
	//if (key == GLUT_KEY_RIGHT)
	//	angle = angle - 5.0;
	if (key == GLUT_KEY_UP)
	{
	//	position.x = position.x - sin(angle * PI / 180.0);
	//	position.z = position.z - cos(angle * PI / 180.0);
		propellerRotForward = true;
		propellerAngle += 5.0f;

	}
	if (key == GLUT_KEY_DOWN)
	{
	//	position.x = position.x + sin(angle * PI / 180.0);
	//	position.z = position.z + cos(angle * PI / 180.0);
		propellerRotBackward = true;
		propellerAngle += 5.0f;
	}

	// Angle correction.
	//if (angle > 360.0)
	//	angle -= 360.0;
	//if (angle < 0.0)
	//	angle += 360.0;

	if (propellerAngle > 360.0)
		propellerAngle -= 360.0;

	//If not holding down acceleration, make this boolean false
	if(key != GLUT_KEY_UP)
		propellerRotForward = false;

	if (key != GLUT_KEY_DOWN)
		propellerRotBackward = false;

}