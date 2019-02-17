#include "Hovercraft.h"

#define PI 3.14159265


Hovercraft::Hovercraft(glm::vec3 position, char *fnameBody, char *fnamePropeller, GLuint uniqueID) : GameObject(position)
{
	Hovercraft::collider = new CubeCollider(&this->position, 5, 5, 5);

	hovercraft.loadModelQuads(fnameBody, uniqueID);
	hovercraftPropeller.loadModelQuads(fnamePropeller, uniqueID);
	propellerRotForward = false;
	propellerRotBackward = false;
	propellerAngle = 0.0f;

	currentSpeed.x = 0.0;
	currentSpeed.y = 0.0;
	currentSpeed.z = 0.0;

	maxSpeed.x = 5.0;
	maxSpeed.y = 5.0;
	maxSpeed.z = 5.0;

	velocity.x = 0.0;
	velocity.y = 0.0;
	velocity.z = 0.0;

	isDecelerating = false;
}

Hovercraft::~Hovercraft()
{
	delete Hovercraft::collider;
	Hovercraft::collider = NULL;
}

void Hovercraft::start(char *fnameBody,char *fnamePropeller, GLuint uniqueID)
{
	hovercraft.loadModelQuads(fnameBody, uniqueID);
	hovercraftPropeller.loadModelQuads(fnamePropeller, uniqueID);
}

float Hovercraft::magnitude(glm::vec3 a)
{
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

void Hovercraft::update(int deltaTime)
{
	float turningSpeed = TURNING_SPEED * (deltaTime / 1000.0); //turning speed (degrees/sec) * deltaTime in sec = turning speed over delta time
	float velocityMagnitude, currentspeedMagnitude, maxspeedMagnitude;//Vector magnitudes

	this->acceleration = this->heading * accelFactor * accelInput; //Computing the acceleration
	glm::vec3 velDelta = velocity * (deltaTime / 1000.0f);

	velocityMagnitude = magnitude(velDelta);

	if (velocityMagnitude != 0) //If magnitude != 0, make current speed equal to normalized velocity vector
		currentSpeed = velDelta;
	else
		currentSpeed = glm::vec3(0, 0, 0);

	currentspeedMagnitude = magnitude(currentSpeed);
	maxspeedMagnitude = magnitude(maxSpeed);

	if (currentspeedMagnitude < maxspeedMagnitude)
			velocity += acceleration;
	
	if (specialKeys[GLUT_KEY_DOWN]) { //Adding deltaTime makes the current speed magnitude static?
		this->position += velDelta;

		propellerRotForward = true;
		propellerRotBackward = false;
		propellerAngle += 5.0f;

		accelInput -= 0.1;

		if (accelInput < -1)
			accelInput = -1;
	}
	else if (specialKeys[GLUT_KEY_UP]) {
		this->position += velDelta;

		propellerRotForward = true;
		propellerRotBackward = false;
		propellerAngle += 5.0f;
		
		accelInput += 0.1;

		if (accelInput > 1)
			accelInput = 1;
	}
	else
	{//Deceleration
		this->position += velDelta;
		velocity *= frictionFactor;
		//Velocity and current speed stay constant after this amount, so I am brute forcing by making them equal to zero
		if (currentspeedMagnitude <= 0.153f)
		{
			velocity = glm::vec3(0, 0, 0);
			currentspeedMagnitude = 0;
		}
	}

	if (specialKeys[GLUT_KEY_PAGE_UP]) {
		this->pitchAngle += turningSpeed; //in degrees not radians
	}

	if (specialKeys[GLUT_KEY_PAGE_DOWN]) {
		this->pitchAngle -= turningSpeed; //in degrees not radians
	}

	if (specialKeys[GLUT_KEY_LEFT]) {
		this->rotationAngle += turningSpeed; //in degrees not radians
		steerInput -= 0.1;
		if (steerInput < -1)
			steerInput = -1;
	}

	if (specialKeys[GLUT_KEY_RIGHT]) {
		this->rotationAngle -= turningSpeed; //in degrees not radians
		steerInput += 0.1;
		if (steerInput > 1)
			steerInput = 1;
	}

	this->heading = glm::rotate(this->startingHeading, glm::radians(rotationAngle), glm::vec3(0.0, 1.0, 0.0));
	
	if (propellerAngle > 360.0)
		propellerAngle -= 360.0;

	//Debugging
	std:: cout << "currentspeedMagnitude: " << currentspeedMagnitude << " maxspeedMagnitude: " << maxspeedMagnitude << " acceleration: " << acceleration.x << " " << acceleration.y << " " << acceleration.z << " " << std::endl;
	std::cout << "Velocity: " <<glm::to_string(velocity) << std::endl;
}

void Hovercraft::draw()
{
	float matAmb1[] = { 0.0, 0.0, 1.0, 1.0 };
	float matDif1[] = { 0.0, 0.0, 1.0, 1.0 };

	glPushMatrix();
		glTranslatef(position.x, position.y, position.z); //Updates the position of the hovercraft
		//glColor3f(0.6, 1, 0.8); //Hovercraft colour
		glScalef(0.4, 0.4, 0.4); 

		glRotatef(pitchAngle, 0, 0, 1);
		glRotatef(rotationAngle, 0, 1, 0); //Rotates the hovercraft when correct keys are inputted
	
		glPushMatrix();
			glRotatef(180, 0, 1, 0); //Rotates the hovercraft into the correct position at start
			//glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb1);
			//glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif1);
			glColor3f(0, 0, 0); //Hovercraft colour
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

	//Heading 
	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(position.x, position.y, position.z);
		glVertex3f(position.x + heading.x * 10, position.y + heading.y * 10, position.z + heading.z * 10);
	glEnd();

	//if (debugMode) {
	
		this->collider->Draw();
	//}
}

void Hovercraft::collides(Collider* other) {
	//if (GameObject::debugMode) {
		std::cout << "Hovercraft collides!" << std::endl;
		velocity.x -= 1;
		//velocity.z -= other->minZ();
	//}
}