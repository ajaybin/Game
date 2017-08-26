#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
class Camera {
	bool firstMouse = true;
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float fov = 45.0f;
	double prevX;
	double prevY;
public:
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up);
	void mouseCallback(double xpos, double ypos);
	void scrollCallback(double xoffset, double yoffset);
	float getFov();
};