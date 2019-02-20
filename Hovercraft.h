#pragma once
#include "GameObject.h"
#include "Reader.h"
#include<iostream>
#include<glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
#include "CubeCollider.h"

#define TURNING_SPEED 90.0 //<turning speed in degrees per second
#define MOVE_SPEED 40.0 //<move speed in coordinate units per second


class Hovercraft : public GameObject
{
private:
	Reader hovercraft, hovercraftPropeller;
	bool propellerRotForward, propellerRotBackward;
	float propellerAngle;

	float accelInput = 0, accelFactor = 0.3;
	float steerAngle, steerInput = 0, steerFactor = 0.01;
	glm::vec3 currentSpeed;
	glm::vec3 maxSpeed;
	glm::vec3 acceleration;
	glm::vec3 velocity;
	bool isDecelerating;

	float frictionFactor = 0.95f;

	//dragC = air drag coefficient; surface area = surface area of front of collider
	float colliderSize, airDrag, dragC, surfaceArea;
public:
	float angle; //Angle of hovercraft movement
	glm::vec3 startingHeading = heading; ///<Starting facing direction of the Hovercraft.
	glm::vec3 newHeading;
	float rotationAngle, pitchAngle = 0.0; ///<Rotation and pitch angles for our Hovercraft
	bool collidesWithGround;
	float groundFriction = 1;
	float velocityMagnitude, currentspeedMagnitude, maxspeedMagnitude;//Vector magnitudes

	Hovercraft(glm::vec3 position, char *fnameBody, char *fnamePropeller, GLuint uniqueID);
	virtual ~Hovercraft();

	virtual void draw();
	virtual void start() {};
	virtual void start(char *fnameBody, char *fnamePropeller, GLuint uniqueID);
	virtual void update(int deltaTime);

	void collides(Collider* other, float materialBounce); ///<Virtual function to notify this game object that a collision has happened can be overridden (optional).

	float magnitude(glm::vec3 a);
};
