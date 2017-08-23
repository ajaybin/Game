#ifndef ENTITY_H
#define ENTITY_H
#include <TexturedModel.h>
#include <glm/glm.hpp>
class Entity {
	TexturedModel model;
public:
	glm::vec3 position;
	float rotX, rotY, rotZ;
	glm::vec3 scale;

	Entity(const TexturedModel model, glm::vec3 position, float rotX, float rotY, float rotZ, glm::vec3 scale);
	TexturedModel getModel();
	void changePosition(float dx, float dy, float dz);
	void changeRotation(float rotX, float rotY, float rotZ);
};
#endif
