#pragma once
#include <glm/glm.hpp>
class Light {
public:
	glm::vec3 position;
	glm::vec3 colour;
	Light(glm::vec3 position, glm::vec3 colour);
};