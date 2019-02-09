#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib") 
#endif 

class Lighting
{
private:
	float ambientStrenght = 0.1f;
	glm::vec3 ambient, result;

public:
	Lighting();
	~Lighting();

	void setupLighting();

	void ambientLight();
};

