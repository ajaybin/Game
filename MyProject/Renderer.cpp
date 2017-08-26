#include "Renderer.h"
Renderer::Renderer(StaticShader &shader, Camera *camera, Light *light) : shader(shader) {
	int params[4];
	glGetIntegerv(GL_VIEWPORT, params);
	this->setAspect(params[2], params[3]);
	this->camera = camera;
	this->light = light;
}
void Renderer::prepare() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(Entity &entity) {
	TexturedModel texModel = entity.getModel();
	RawModel model = texModel.getRawModel();
	glBindVertexArray(model.getVAO());

	glm::mat4 modelMat = Maths::createModelMatrix(entity.position, entity.rotX, entity.rotY, entity.rotZ, entity.scale);
	shader.setMat4("modelMatrix", modelMat);
	glm::mat4 projectionMatrix = Maths::createProjectionMatrix(camera->getFov(), (float)this->width / (float)this->height, 0.1f, 100.0f);
	shader.setMat4("projectionMatrix", projectionMatrix);
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera->position, camera->position + camera->target);
	shader.setMat4("viewMatrix", viewMatrix);
	shader.setVec3("lightPosition", light->position);
	shader.setVec3("lightColour", light->colour);

	for (unsigned int i = 0; i < texModel.getModelTex().getNumTextures(); i++) {
		shader.setInt(("textureSampler" + std::to_string(i)).c_str(), i);
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texModel.getModelTex().getTexture(i));
	}
	glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer::setAspect(int width, int height) {
	this->width = width;
	this->height = height;
}
