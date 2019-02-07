#pragma once
#include "GameObject.h"
#include "Reader.h"

class Racetrack : public GameObject
{
private:
	Reader racetrack;
	float racetrackrot; //Used to rotate the racetrack to view it from different angles
public:
	Racetrack(glm::vec3 position, char *fname, GLuint uniqueID);
	virtual ~Racetrack();

	virtual void draw();
	virtual void start() {};
	virtual void start(char *fname, GLuint uniqueID);
	virtual void update(int deltaTime);
};

