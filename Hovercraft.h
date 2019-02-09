#pragma once
#include "GameObject.h"
#include "Reader.h"

class Hovercraft : public GameObject
{
private:
	Reader hovercraft;
public:
	float angle; //Angle of hovercraft movement

	Hovercraft(glm::vec3 position, char *fname, GLuint uniqueID);
	virtual ~Hovercraft();

	virtual void draw();
	virtual void start() {};
	virtual void start(char *fname, GLuint uniqueID);
	virtual void update(int deltaTime);

	void movement(int key);
};
