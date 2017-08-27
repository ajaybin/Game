#include "Renderer.h"
Renderer::Renderer(StaticShader *shader) {

	this->shader = shader;

	int params[4];
	glGetIntegerv(GL_VIEWPORT, params);
	this->setAspect(params[2], params[3]);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}
void Renderer::prepare() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(std::map<TexturedModel*, std::vector<Entity>> *entities) {
	for (auto& it : *entities) {
		TexturedModel *texModel = it.first;
		prepareTexturedModel(texModel);
		std::vector<Entity> entityVector = it.second;
		for (Entity entity : entityVector) {
			prepareEntity(entity);
			glDrawElements(GL_TRIANGLES, texModel->getRawModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		unbindTexturedModel();
	}
}

void Renderer::prepareTexturedModel(TexturedModel *texModel) {
	RawModel *model = texModel->getRawModel();
	glBindVertexArray(model->getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	for (unsigned int i = 0; i < texModel->getModelTex()->getNumTextures(); i++) {
		shader->setInt(("textureSampler" + std::to_string(i)).c_str(), i);
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texModel->getModelTex()->getTexture(i));
	}
	shader->setFloat("reflectivity", texModel->getModelTex()->getReflectivity());
	shader->setFloat("shineFactor", texModel->getModelTex()->getShineFactor());
}

void Renderer::unbindTexturedModel() {
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Renderer::prepareEntity(Entity & entity) {
	glm::mat4 modelMat = Maths::createModelMatrix(entity.position, entity.rotX, entity.rotY, entity.rotZ, entity.scale);
	shader->setMat4("modelMatrix", modelMat);
}

void Renderer::setAspect(int width, int height) {
	this->width = width;
	this->height = height;
}
