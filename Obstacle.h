#pragma once
#include "GameObject.h"

//Class for game obstacles
class Obstacle : public GameObject
{
private:
	glm::vec3 colour; //Object colour
public:
	Obstacle(glm::vec3 position, glm::vec3 objColour = {0, 0, 1});
	~Obstacle();

	void draw();
	void start();
	void update(int deltaTime);
	unsigned int setupDrawing(unsigned int listBase);
};

