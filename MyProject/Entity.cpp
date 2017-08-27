#include "Entity.h"

Entity::Entity(TexturedModel* model, glm::vec3 position, float rotX, float rotY, float rotZ, glm::vec3 scale) {
	this->position = position;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = scale;
	this->model = model;
}

TexturedModel* Entity::getModel() {
	return this->model;
}

void Entity::changePosition(float dx, float dy, float dz) {
	this->position.x += dx;
	this->position.y += dy;
	this->position.z += dz;
}

void Entity::changeRotation(float rotX, float rotY, float rotZ) {
	this->rotX += rotX;
	this->rotY += rotY;
	this->rotZ += rotZ;
}
