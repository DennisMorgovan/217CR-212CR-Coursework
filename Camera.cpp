#include "Camera.h"

Camera::Camera(Hovercraft* hovercraft, glm::vec3 cameraUp, glm::vec3 cameraCorrection)
{
	this->cameraUp = cameraUp;
	this->hovercraft = hovercraft;
	this->cameraCorrection = cameraCorrection;
	this->buttonDown = -1;
	this->deltaAngle = 0.0f;
	this->angle = 0.0f;
}

Camera::~Camera()
{

}

void Camera::update()
{
	cameraPos = hovercraft->position + cameraCorrection;
	cameraTarget = hovercraft->position;

	cameraPos.x += heading;
	cameraPos.z += pitch;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, cameraTarget.x, cameraTarget.y, cameraTarget.z, cameraUp.x, cameraUp.y, cameraUp.z);
}

void Camera::mouseControl(int key, int state, int x, int y)
{
	if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		
		//if (state == GLUT_UP)
		//	buttonDown = -1;
		//else
			buttonDown = x;
			angle += 3.0f;
	}

	glutPostRedisplay();
}

void Camera::mouseMotion(int x, int y)
{
	int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	deltaX = x - centerX;
	deltaY = y - centerY;



	if (deltaX != 0 || deltaY != 0)
	{

		heading = deltaX * 0.2f;
		pitch = deltaY * 0.2f;
	}

	//if (heading > 360)
	//	heading -= 360;
	//if (pitch > 360)
	//	pitch -= 360;
	glutPostRedisplay();
}