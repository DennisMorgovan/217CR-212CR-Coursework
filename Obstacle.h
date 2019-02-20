#pragma once
#include "GameObject.h"

//Class for game obstacles
class Obstacle : public GameObject
{
private:
	glm::vec3 colour; //Object colour
public:
	float materialBounce;
	Obstacle(glm::vec3 position, glm::vec3 objColour = {0, 0, 1}, float matBounce = 5);

	~Obstacle();

	void collides(Collider* other); ///<Virtual function to notify this game object that a collision has happened can be overridden (optional).

	void draw();
	void start();
	void update(int deltaTime);
	unsigned int setupDrawing(unsigned int listBase);
};

