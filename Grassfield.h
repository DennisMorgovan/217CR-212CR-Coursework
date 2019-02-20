#pragma once
#include "GameObject.h"
#include "Reader.h"
#include<iostream>
#include<glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
#include "CubeCollider.h"

class Grassfield : public GameObject
{
private:
	Reader grass;

public:
	Grassfield(glm::vec3 position, char *fname, GLuint uniqueID);
	~Grassfield();

	virtual void start() {};
	virtual void start(char *fname, GLuint uniqueID);
	virtual void update(int deltaTime);
	virtual void draw();
};

