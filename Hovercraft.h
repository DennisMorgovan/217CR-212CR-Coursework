#pragma once
#include "GameObject.h"
#include "Reader.h"

class Hovercraft : public GameObject
{
private:
	Reader hovercraft, hovercraftPropeller;
	bool propellerRot;
	float propellerAngle;
public:
	float angle; //Angle of hovercraft movement

	Hovercraft(glm::vec3 position, char *fnameBody, char *fnamePropeller, GLuint uniqueID);
	virtual ~Hovercraft();

	virtual void draw();
	virtual void start() {};
	virtual void start(char *fnameBody, char *fnamePropeller, GLuint uniqueID);
	virtual void update(int deltaTime);

	void movement(int key);
};
