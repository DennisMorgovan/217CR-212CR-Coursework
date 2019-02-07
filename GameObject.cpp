#include "GameObject.h"

unsigned int GameObject::setupDrawing(unsigned int listBase)
{
	return 0;
}

void GameObject::draw()
{
}

GameObject::GameObject(glm::vec3 position)
{
	this->position = position;
}


GameObject::~GameObject()
{
}
