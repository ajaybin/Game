#include <iostream>
#include <random>
#include <MasterRenderer.h>
#include <BaseRenderer.h>
#include <Player.h>
using namespace std;

const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame


Camera *camera;
Player *player;

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	camera->mouseCallback(xpos, ypos);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		//camera->moveCamera(window, deltaTime);
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera->scrollCallback(xoffset, yoffset);
}

int main() {
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

	Loader *loader = new Loader(); 
	Light *light = new Light(glm::vec3(0.0f, 100.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));;
	camera = new Camera(glm::vec3(0.0f, 5.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));


	RawModel bunnyModel = loader->loadObjFromFile("res/cube.obj");
	ModelTex *bunnyTex = new ModelTex(32, 0.2f);
	bunnyTex->addTexture(loader->loadTexture("res/slateRoof.png"));
	TexturedModel *bunnyTexModel = new TexturedModel(&bunnyModel, bunnyTex);
	player = new Player(bunnyTexModel, glm::vec3(0.0f, 0.5f, 0.0f), 0.0f, 0.0f, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	RawModel model = loader->loadObjFromFile("res/fern.obj");
	ModelTex *tex = new ModelTex(32, 0.5);
	tex->addTexture(loader->loadTexture("res/fern.png"));
	tex->isTransparent = true;
	TexturedModel *texModel = new TexturedModel(&model, tex);

	RawModel grassModel = loader->loadObjFromFile("res/grassModel.obj");
	ModelTex *gTex = new ModelTex(32, 0.1f);
	gTex->addTexture(loader->loadTexture("res/grassTexture.png"));
	gTex->isTransparent = true;
	gTex->useFakeLight = true;
	TexturedModel *grassTexModel = new TexturedModel(&grassModel, gTex);

	//Wow much confuse C++11
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);

	std::vector<Entity> entityVector;
	for (int i = 0; i < 200; i++) {
		float x = ((float)dis(gen) * 1600) - 800;
		float y = 0.0f;
		float z = ((float)dis(gen) * 1600) - 800;
		Entity entity(texModel, glm::vec3(x, y, z), 0.0f, (float)dis(gen) * 180.0f, 0, glm::vec3(1.0f, 1.0f, 1.0f));
		entityVector.push_back(entity);
	}

	for (int i = 0; i < 2000; i++) {
		float x = ((float)dis(gen) * 1600) - 800;
		float y = 0.0f;
		float z = ((float)dis(gen) * 1600) - 800;
		Entity entity(grassTexModel, glm::vec3(x, y, z), 0.0f, (float)dis(gen) * 180.0f, 0, glm::vec3(1.0f, 1.0f, 1.0f));
		entityVector.push_back(entity);
	}

	ModelTex *grassTex = new ModelTex(32, 0.1f);
	grassTex->addTexture(loader->loadTexture("res/grass.jpg"));
	grassTex->addTexture(loader->loadTexture("res/mud.png"));
	grassTex->addTexture(loader->loadTexture("res/grassFlowers.png"));
	grassTex->addTexture(loader->loadTexture("res/path.png"));
	grassTex->addTexture(loader->loadTexture("res/blendmap1.png"));
	Terrain terrain1(-1, 0, loader, grassTex);
	Terrain terrain2(0, 0, loader, grassTex);
	Terrain terrain3(-1, -1, loader, grassTex);
	Terrain terrain4(0, -1, loader, grassTex);

	MasterRenderer *renderer = new MasterRenderer();

	while(!glfwWindowShouldClose(window)) {
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		player->move(window, deltaTime);
		//Input
		processInput(window);
		//Render
		for (Entity entity : entityVector) {
			renderer->addEntity(entity);
		}
		renderer->addEntity(*player);
		renderer->addTerrain(terrain1);
		renderer->addTerrain(terrain2);
		renderer->addTerrain(terrain3);
		renderer->addTerrain(terrain4);
		renderer->render(camera, light);
		//check event and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	renderer->cleanUp();
	loader->cleanUp();
	glfwTerminate();
	delete loader, tex, grassTex, gTex, texModel, grassTexModel, renderer, camera, light, player;
	return 0;
}

