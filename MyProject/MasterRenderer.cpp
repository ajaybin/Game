#include "MasterRenderer.h"

MasterRenderer::MasterRenderer() {
	shader = new StaticShader();
	entityRenderer = new EntityRenderer(shader);

	terrainShader = new TerrainShader();
	terrainRenderer = new TerrainRenderer(terrainShader);

	this->entities = new std::map<TexturedModel*, std::vector<Entity>>();
}

void MasterRenderer::cleanUp() {
	shader->cleanUp();
	terrainShader->cleanUp();
	delete shader;
	delete entityRenderer;
	delete terrainShader;
	delete terrainRenderer;
	delete entities;
}

void MasterRenderer::render(Camera *camera, Light *light) {
	glm::mat4 projectionMatrix = Maths::createProjectionMatrix(camera->getFov(), 1280.0f / 720.0f, NEAR_PLANE, FAR_PLANE);
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera->position, camera->position + camera->target);

	prepare();

	shader->start();
	shader->setVec3("lightPosition", light->position);
	shader->setVec3("lightColour", light->colour);
	shader->setMat4("viewMatrix", viewMatrix);
	shader->setMat4("projectionMatrix", projectionMatrix);
	shader->setVec3("cameraPosition", camera->position);
	shader->setVec3("skyColour", glm::vec3(RED, GREEN, BLUE));
	entityRenderer->render(entities);
	shader->end();

	terrainShader->start();
	terrainShader->setVec3("lightPosition", light->position);
	terrainShader->setVec3("lightColour", light->colour);
	terrainShader->setMat4("viewMatrix", viewMatrix);
	terrainShader->setMat4("projectionMatrix", projectionMatrix);
	terrainShader->setVec3("cameraPosition", camera->position);
	terrainShader->setVec3("skyColour", glm::vec3(RED, GREEN, BLUE));
	terrainRenderer->render(terrains);
	terrainShader->end();

	terrains.clear();
	entities->clear();
}

void MasterRenderer::addEntity(Entity & entity) {
	if (entities->find(entity.getModel()) != entities->end()) {
		std::vector<Entity> *entityVector = &entities->at(entity.getModel());
		entityVector->push_back(entity);
	}
	else {
		std::vector<Entity> entityVector;
		entityVector.push_back(entity);
		entities->insert(std::pair<TexturedModel*, std::vector<Entity>>(entity.getModel(), entityVector));
	}
}

void MasterRenderer::addTerrain(Terrain & terrain) {
	terrains.push_back(terrain);
}

void MasterRenderer::prepare() {
	glEnable(GL_DEPTH_TEST);
	//glClearColor(0.53f, 0.80f, 0.98f, 1.0f);
	glClearColor(RED, GREEN, BLUE, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}