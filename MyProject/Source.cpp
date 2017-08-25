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
using namespace std;

const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, Camera &camera) {
	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.position -= cameraSpeed * camera.target;
	}
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.position += cameraSpeed * camera.target;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.position += glm::normalize(glm::cross(camera.up, camera.target)) * cameraSpeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.position -= glm::normalize(glm::cross(camera.up, camera.target)) * cameraSpeed;
	}
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

	//RawModel model = loader.loadObjFromFile("res/stall.obj");
	RawModel model = loader.loadObjFromFile("res/cube.obj");
	ModelTex tex;
	tex.addTexture(loader.loadTexture("res/container.jpg"));
	TexturedModel texModel(model, tex);
	Entity entity(texModel, glm::vec3(0.0f, 0.0f, -5.0f), 0, 0, 0, glm::vec3(1.0f, 1.0f, 1.0f));
	Entity entity2(texModel, glm::vec3(3.0f, 5.0f, -20.0f), 0, 0, 0, glm::vec3(1.0f, 1.0f, 1.0f));
	StaticShader shader;
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 3.0f) + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	while(!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//entity.changePosition(0.0f, 0.0f, -0.0001f);
		//entity.changeRotation(0.02f, 0.02f, 0.0f);
		//Input
		processInput(window, camera);
		//Render
		Renderer renderer(shader, camera, WIDTH, HEIGHT);
		renderer.prepare();
		shader.start();
		renderer.render(entity);
		renderer.render(entity2);
		shader.end();
		//check event and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	loader.cleanUp();
	glfwTerminate();
	return 0;
}

