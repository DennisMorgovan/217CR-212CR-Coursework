#include "CubeCollider.h"

CubeCollider::CubeCollider(glm::vec3 * centre, float cubeWidth, float cubeHeight, float cubeLength)
{
	this->colliderCentre = centre;
	this->width = cubeWidth;
	this->height = cubeHeight;
	this->length = cubeLength;
}

CubeCollider::~CubeCollider()
{
}

bool CubeCollider::collidesWith(Collider * other)
{
	if (other == NULL) {
		return false;
	}

	bool overlapX = other->minX() <= this->maxX() && other->maxX() >= this->minX();
	bool overlapY = other->minY() <= this->maxY() && other->maxY() >= this->minY();
	bool overlapZ = other->minZ() <= this->maxZ() && other->maxZ() >= this->minZ();
	return overlapX && overlapY && overlapZ;
}

float CubeCollider::minX()
{
	return this->colliderCentre->x - this->width / 2;
}

float CubeCollider::maxX()
{
	return this->colliderCentre->x + this->width / 2;
}

float CubeCollider::minY()
{
	return this->colliderCentre->y - this->height / 2;
}

float CubeCollider::maxY()
{
	return this->colliderCentre->y + this->height / 2;
}

float CubeCollider::minZ()
{
	return this->colliderCentre->z - this->length / 2;
}

float CubeCollider::maxZ()
{
	return this->colliderCentre->z + this->length / 2;
}

void CubeCollider::Draw()
{
}
