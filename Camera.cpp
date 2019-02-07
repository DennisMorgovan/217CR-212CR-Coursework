#include "Camera.h"

Camera::Camera(Hovercraft* hovercraft, glm::vec3 cameraUp, glm::vec3 cameraCorrection)
{
	this->cameraUp = cameraUp;
	this->hovercraft = hovercraft;
	this->cameraCorrection = cameraCorrection;

}

Camera::~Camera()
{

}

void Camera::update()
{
	cameraPos = hovercraft->position + cameraCorrection;
	cameraTarget = hovercraft->position;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, cameraTarget.x, cameraTarget.y, cameraTarget.z, cameraUp.x, cameraUp.y, cameraUp.z);
}