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

public:
	glm::vec3 cameraPos, cameraTarget, cameraUp, cameraCorrection;

	Camera(Hovercraft* hovercraft, glm::vec3 cameraUp, glm::vec3 cameraCorrection);
	~Camera();

	//void start(Hovercraft hovercraft, glm::vec3 cameraUp, glm::vec3 cameraCorrection);
	void update();
};

