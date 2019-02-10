#pragma once
#include "GameObject.h"
#include "Reader.h"
#include<iostream>
#include<glm/gtx/rotate_vector.hpp>
#define TURNING_SPEED 90.0 //<turning speed in degrees per second
#define MOVE_SPEED 40.0 //<move speed in coordinate units per second

class Hovercraft : public GameObject
{
private:
	Reader hovercraft, hovercraftPropeller;
	bool propellerRotForward, propellerRotBackward;
	float propellerAngle;
public:
	float angle; //Angle of hovercraft movement
	glm::vec3 startingHeading = heading; ///<Starting facing direction of the Hovercraft.
	float rotationAngle, pitchAngle = 0.0; ///<Rotation and pitch angles for our Hovercraft

	Hovercraft(glm::vec3 position, char *fnameBody, char *fnamePropeller, GLuint uniqueID);
	virtual ~Hovercraft();

	virtual void draw();
	virtual void start() {};
	virtual void start(char *fnameBody, char *fnamePropeller, GLuint uniqueID);
	virtual void update(int deltaTime);

	void movement(int key);
};
