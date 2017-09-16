#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
	this->position = position;
	this->target = target;
	this->up = up;
	int params[4];
	glGetIntegerv(GL_VIEWPORT, params);
	prevX = params[2] / 2;
	prevY = params[3] / 2;
}

void Camera::mouseCallback(double xpos, double ypos) {
	if (firstMouse) {
		prevX = xpos;
		prevY = ypos;
		firstMouse = false;
	}

	float xOffset = (float)xpos - (float)prevX;
	float yOffset = (float)prevY - (float)ypos;
	prevX = xpos;
	prevY = ypos;
	float sensitivity = 0.08f;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw = std::fmod(yaw + xOffset, 360.0f);
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->target = glm::normalize(front);
}

void Camera::scrollCallback(double xoffset, double yoffset) {
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= (float)yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}

void Camera::moveCamera(GLFWwindow *window, float deltaTime) {
	float cameraSpeed = 10.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= cameraSpeed * target;
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += cameraSpeed * target;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position += glm::normalize(glm::cross(up, target)) * cameraSpeed;
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position -= glm::normalize(glm::cross(up, target)) * cameraSpeed;
}

float Camera::getFov() {
	return fov;
}
