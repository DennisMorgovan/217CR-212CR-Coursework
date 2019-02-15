#include "GameObject.h"

bool GameObject::debugMode;

unsigned int GameObject::setupDrawing(unsigned int listBase)
{
	return 0;
}

void GameObject::draw()
{
}

void GameObject::collides(Collider * other)
{

}

GameObject::GameObject(glm::vec3 position)
{
	this->position = position;
}


GameObject::~GameObject()
{
}
