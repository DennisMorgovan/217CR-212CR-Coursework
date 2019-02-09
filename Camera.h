#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib") 
#endif 

#include "Hovercraft.h"

class Camera
{
private:
	Hovercraft* hovercraft;
	float buttonDown, deltaAngle; //buttonDown determines whether the left mouse button is being held or not (-1 if it isn't / any other value if it is); deltaAngle is the difference between the final angle and the initial angle of the mouse
	float angle;
	float heading, pitch;
	float deltaX, deltaY;
public:
	glm::vec3 cameraPos, cameraTarget, cameraUp, cameraCorrection;

	Camera(Hovercraft* hovercraft, glm::vec3 cameraUp, glm::vec3 cameraCorrection);
	~Camera();

	//void start(Hovercraft hovercraft, glm::vec3 cameraUp, glm::vec3 cameraCorrection);
	void update();

	void mouseControl(int key, int state, int x, int y);
	void mouseMotion(int x, int y);
};

