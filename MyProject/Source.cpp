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
using namespace std;

const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main() {

	Loader loader;
	std::vector<float> vertices = {-0.5f, -0.5f, 0.0f,
	                                0.5f, -0.5f, 0.0f,
	                                0.5f,  0.5f, 0.0f,
	                               -0.5f,  0.5f, 0.0f};
	std::vector<int> indices = {0, 1, 2, 2, 3, 0};
	std::vector<float> texCoords = {0.0f, 1.0f,
	                                1.0f, 1.0f,
	                                1.0f, 0.0f,
	                                0.0f, 0.0f};

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

	RawModel model = loader.loadObjIntoVAO(vertices, texCoords, indices);
	ModelTex tex;
	tex.addTexture(loader.loadTexture("res/container.jpg"));
	tex.addTexture(loader.loadTexture("res/awesomeface.png"));
	TexturedModel texModel(model, tex);
	Entity entity(texModel, glm::vec3(0.0f, 0.0f, 0.0f), 0, 0, 0, glm::vec3(1.0f, 1.0f, 1.0f));
	StaticShader shader;
	Renderer renderer(shader);
	while(!glfwWindowShouldClose(window)) {
		entity.changePosition(0.0f, 0.00002f, 0.0f);
		entity.changeRotation(0.0f, 0.0f, 0.0001f);
		//Input
		processInput(window);
		//Render
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
	return 0;
}

