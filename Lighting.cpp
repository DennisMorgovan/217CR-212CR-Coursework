#include "Lighting.h"



Lighting::Lighting()
{

}


Lighting::~Lighting()
{
}

void Lighting::setupLighting()
{
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	//glColorMaterial(GL_FRONT, GL_AMBIENT);
	//glColorMaterial(GL_FRONT, GL_DIFFUSE);
	//glColorMaterial(GL_FRONT, GL_SPECULAR);

	/* turn on default lighting */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void Lighting::ambientLight()
{
	glm::vec3 lightColour(1, 1, 1);

	glm::vec3 ambient = ambientStrenght * lightColour;

	//glm::vec3 result = ambient * 
}
