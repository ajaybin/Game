#include "MasterRenderer.h"

MasterRenderer::MasterRenderer() {
	shader = new StaticShader();
	renderer = new Renderer(shader);
	this->entities = new std::map<TexturedModel*, std::vector<Entity>>();
}

void MasterRenderer::cleanUp() {
	shader->cleanUp();
}

void MasterRenderer::render(Camera *camera, Light *light) {
	renderer->prepare();
	shader->start();
	shader->setVec3("lightPosition", light->position);
	shader->setVec3("lightColour", light->colour);
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera->position, camera->position + camera->target);
	shader->setMat4("viewMatrix", viewMatrix);
	glm::mat4 projectionMatrix = Maths::createProjectionMatrix(camera->getFov(), 1280.0f / 720.0f, 0.1f, 100.0f);
	shader->setMat4("projectionMatrix", projectionMatrix);
	shader->setVec3("cameraPosition", camera->position);
	renderer->render(entities);
	shader->end();
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
