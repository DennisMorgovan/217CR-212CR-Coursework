#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib") 
#endif 

#include "Hovercraft.h"

class Lighting
{
private:
	
	float d = 1.0; // Diffuse and specular white light intensity.
	float m = 0.2; // Global ambient white light intensity.
	int localViewer = 1; // Local viewpoint?
	float p = 1.0; // Positional light?
	float xAngle = 0.0, yAngle = 0.0; // Rotation angles of white light.
public:
	int spotlightOn = -1;

	Lighting();
	~Lighting();

	void setupLighting();

	void drawLighting();

	void drawSpotlight(Hovercraft *hovercraft);
};

