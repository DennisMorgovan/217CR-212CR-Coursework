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

	/* turn on default lighting */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHT1);

	// Light property vectors.
	//float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	//float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	//float globAmb[] = { 0.05, 0.05, 0.05, 1.0 };

	// Light properties.
	//glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec);

	// Material property vectors.
	float matAmbAndDif[] = { 0.0, 0.0, 1.0, 1.0 };
	float matSpec[] = { 0.2, 0.2, 0.2, 0.2 };
	float matShine[] = { 100.0 };

	// Material properties of sphere.
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glColorMaterial(GL_FRONT, GL_SPECULAR);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void Lighting::drawLighting()
{
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDifAndSpec0[] = { d, d, d, 1.0 };
	float lightPos0[] = { 0.0, 0.0, 3.0, p };
	float globAmb[] = { m, m, m, 1.0 };


	// Light0 properties.
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec0);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, localViewer); // Enable local viewpoint

	// Draw light source spheres (or arrow) after disabling lighting.
	glDisable(GL_LIGHTING);

	//Sets light position
	glPushMatrix();
		lightPos0[0] = 0; lightPos0[1] = 100; lightPos0[2] = 0.0;
		glRotatef(45, 1, 0, 0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
		glTranslatef(lightPos0[0], lightPos0[1], lightPos0[2]);
		glColor3f(d, d, d);
	glPopMatrix();

	glPushMatrix();
		glColor3f(d, d, d);
		glTranslatef(lightPos0[0], lightPos0[1], lightPos0[2]);
		glScalef(30, 30, 30);
		if (p) 
			glutWireSphere(0.05, 8, 8); // Sphere at positional light source.
	glPopMatrix();

	glEnable(GL_LIGHTING);
}

void Lighting::drawSpotlight(Hovercraft *hovercraft)
{
	float lightPos[] = { hovercraft->position.x, hovercraft->position.y + 20, hovercraft->position.z, 1.0 }; // Spotlight position.
	static float spotAngle = 50.0; // Spotlight cone half-angle.
	float spotDirection[] = { hovercraft->heading.x, -1.0, hovercraft->heading.z }; // Spotlight direction.
	static float spotExponent = 2.0; // Spotlight exponent = attenuation factor.

	glPushMatrix();
	// Spotlight properties including position.
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotAngle);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent);
	glPopMatrix();


	if (spotlightOn == -1)
	{
		// Draw the spotlight cone in wireframe after disabling lighting
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glRotatef(0, 90, 0, 1);
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(hovercraft->position.x + hovercraft->heading.x, 0.0, hovercraft->position.z + hovercraft->heading.z);
		glRotatef(hovercraft->rotationAngle, 0, 1, 0);
		glutWireCone(3.0 * tan(spotAngle / 180.0 * 3.1415), 3.0, 20, 20);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
}
