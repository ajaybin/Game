#pragma once
#include <glfw3.h>
#include <Entity.h>
#include <glm\glm.hpp>
#include <iostream>
using namespace std;

class Player : public Entity {
	static const float RUN_SPEED;
	static const float TURN_SPEED;
	static const float GRAVITY;
	static const float UP_SPEED;
	static const float TERRAIN_HEIGHT;

	float currentSpeed = 0;
	float currentTurnSpeed = 0;
	float upSpeed = 0;
	bool isInAir = false;
public:
	Player(TexturedModel *model, glm::vec3 position, float rotX, float rotY, float rotZ, glm::vec3 scale);
	void move(GLFWwindow* window, float deltaTime);
	void checkInputs(GLFWwindow* window);
};
