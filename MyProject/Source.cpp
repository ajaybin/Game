#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <RawModel.h>
#include <Loader.h>
#include <Renderer.h>
#include <StaticShader.h>
#include <ModelTex.h>
#include <TexturedModel.h>
#include <Entity.h>
#include <Maths.h>
#include <Camera.h>
#include <Light.h>
using namespace std;

const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame


Camera *camera;

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	camera->mouseCallback(xpos, ypos);
}

void processInput(GLFWwindow* window) {
	float cameraSpeed = 5.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->position -= cameraSpeed * camera->target;
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->position += cameraSpeed * camera->target;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->position += glm::normalize(glm::cross(camera->up, camera->target)) * cameraSpeed;
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->position -= glm::normalize(glm::cross(camera->up, camera->target)) * cameraSpeed;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera->scrollCallback(xoffset, yoffset);
}

int main() {

	Loader loader;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "MyWindow", NULL, NULL);

	if (window == NULL) {
		std::cout << "FAILED to create window";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "FAILED to intialize GLAD";
		glfwTerminate();
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Light *light;
	light = new Light(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	RawModel model = loader.loadObjFromFile("res/stall.obj");
	ModelTex tex(32, 1);
	tex.addTexture(loader.loadTexture("res/stallTexture.png"));
	TexturedModel texModel(model, tex);
	Entity entity(texModel, glm::vec3(0.0f, -2.0f, -10.0f), 0, 0, 0, glm::vec3(1.0f, 1.0f, 1.0f));
	StaticShader shader;
	while(!glfwWindowShouldClose(window)) {
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		entity.changeRotation(0.0f, 0.005f, 0.0f);

		//Input
		processInput(window);
		//Render
		Renderer renderer(shader, camera, light);
		renderer.prepare();
		shader.start();
		renderer.render(entity);
		shader.end();
		//check event and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	loader.cleanUp();
	glfwTerminate();
	delete camera;
	delete light;
	return 0;
}

