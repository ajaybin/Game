#include "Player.h"

const float Player::RUN_SPEED = 10.0f;
const float Player::TURN_SPEED = 120.0f;
const float Player::GRAVITY = -50.0f;
const float Player::UP_SPEED = 30.0f;

const float Player::TERRAIN_HEIGHT = 0.0f;

Player::Player(TexturedModel * model, glm::vec3 position, float rotX, float rotY, float rotZ, glm::vec3 scale) : 
Entity(model, position, rotX, rotY, rotZ, scale) {
}

void Player::move(GLFWwindow * window, float deltaTime) {
	checkInputs(window);
	this->changeRotation(0.0f, deltaTime * currentTurnSpeed, 0.0f);
	float distance = currentSpeed * deltaTime;
	float dx = distance * glm::sin(glm::radians(this->rotY));
	float dz = distance * glm::cos(glm::radians(this->rotY));
	this->changePosition(dx, 0.0f, dz);
	upSpeed += GRAVITY * deltaTime;
	this->changePosition(0.0f, upSpeed * deltaTime, 0.0f);
	if (this->position.y < 0.0f) {
		upSpeed = 0.0f;
		this->position.y = 0.0f;
		isInAir = false;
	}
}

void Player::checkInputs(GLFWwindow * window) {
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		currentSpeed = +RUN_SPEED;
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		currentSpeed = -RUN_SPEED;
	else 
		currentSpeed = 0;
	
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		currentTurnSpeed = +TURN_SPEED;
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		currentTurnSpeed = -TURN_SPEED;
	else
		currentTurnSpeed = 0;

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (!isInAir) {
			upSpeed = UP_SPEED;
			isInAir = true;
		}
	}
}
