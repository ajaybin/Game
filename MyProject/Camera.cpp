#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
	this->position = position;
	this->target = target;
	this->up = up;
}
