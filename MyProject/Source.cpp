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
	std::vector<float> vertices = 
	 {  -0.5f,0.5f,-0.5f,
	    -0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,0.5f,-0.5f,

		-0.5f,0.5f,0.5f,
		-0.5f,-0.5f,0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		0.5f,0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
		-0.5f,0.5f,0.5f,

		-0.5f,0.5f,0.5f,
		-0.5f,0.5f,-0.5f,
		0.5f,0.5f,-0.5f,
		0.5f,0.5f,0.5f,

		-0.5f,-0.5f,0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f };
	std::vector<int> indices = 
	  { 0,1,3,
		3,1,2,
		4,5,7,
		7,5,6,
		8,9,11,
		11,9,10,
		12,13,15,
		15,13,14,
		16,17,19,
		19,17,18,
		20,21,23,
		23,21,22 };
	std::vector<float> texCoords = 
	  { 0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0 };

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

	RawModel model = loader.loadObjFromFile("res/stall.obj");
	model = loader.loadObjIntoVAO(vertices, texCoords, indices);
	ModelTex tex;
	tex.addTexture(loader.loadTexture("res/container.jpg"));
	//tex.addTexture(loader.loadTexture("res/awesomeface.png"));
	TexturedModel texModel(model, tex);
	Entity entity(texModel, glm::vec3(0.0f, 0.0f, 0.0f), 0, 0, 0, glm::vec3(1.0f, 1.0f, 1.0f));
	entity.changeRotation(-55.0f, 0.0f, 0.0f);
	StaticShader shader;
	Renderer renderer(shader, WIDTH, HEIGHT);
	while(!glfwWindowShouldClose(window)) {
		//entity.changePosition(0.0f, 0.0f, -0.0001f);
		entity.changeRotation(0.01f, 0.02f, 0.02f);
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

