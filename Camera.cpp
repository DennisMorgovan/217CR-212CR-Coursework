#include "Camera.h"


#define PI 3.14159265

Camera::Camera(Hovercraft* hovercraft, glm::vec3 cameraUp, glm::vec3 cameraCorrection)
{
	this->cameraUp = cameraUp;
	this->hovercraft = hovercraft;
	this->cameraCorrection = cameraCorrection;
	this->buttonDown = -1;
	this->deltaAngle = 0.0f;
	this->angle = 0.0f;

	this->cameraMode = 0;
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

	if (cameraMode == 0)
		gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, cameraTarget.x, cameraTarget.y, cameraTarget.z, cameraUp.x, cameraUp.y, cameraUp.z); //3rd person view from the back
	else if (cameraMode == 1)
		gluLookAt(cameraPos.x, cameraPos.y + 50, cameraPos.z, cameraTarget.x, cameraTarget.y, cameraTarget.z, cameraUp.x, cameraUp.y, cameraUp.z); //View from the top
	else if (cameraMode == 2)
		gluLookAt(cameraPos.x - 20 * sin(hovercraft->angle * PI / 180.0), cameraPos.y, cameraPos.z, cameraTarget.x, cameraTarget.y, cameraTarget.z, cameraUp.x, cameraUp.y, cameraUp.z); //View from the front
	else if (cameraMode == 3) //Side camera right
		gluLookAt(cameraTarget.x, 15, cameraTarget.z - 20 * sin(hovercraft->angle * PI / 180.0), cameraTarget.x, 0.0, cameraTarget.z, 0.0, 1.0, 0.0);
	else if (cameraMode == 4) //Side camera left
		gluLookAt(cameraTarget.x, 15, cameraTarget.z + 20 * sin(hovercraft->angle * PI / 180.0), cameraTarget.x, 0.0, cameraTarget.z, 0.0, 1.0, 0.0);
}

void Camera::mouseControl(int key, int state, int x, int y)
{
	if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
			buttonDown = x;
			angle += 3.0f;
	}
	if (key == GLUT_RIGHT_BUTTON)
		exit(0);
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

	glutPostRedisplay();
}