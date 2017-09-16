#include "EntityRenderer.h"
EntityRenderer::EntityRenderer(StaticShader *shader) {

	this->shader = shader;
}

void EntityRenderer::render(std::map<TexturedModel*, std::vector<Entity>> *entities) {
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

void EntityRenderer::prepareTexturedModel(TexturedModel *texModel) {
	RawModel *model = texModel->getRawModel();
	glBindVertexArray(model->getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	if (texModel->getModelTex()->isTransparent) {
		disableBackCulling();
	}
	for (unsigned int i = 0; i < texModel->getModelTex()->getNumTextures(); i++) {
		shader->setInt(("textureSampler" + std::to_string(i)).c_str(), i);
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texModel->getModelTex()->getTexture(i));
	}
	shader->setFloat("reflectivity", texModel->getModelTex()->getReflectivity());
	shader->setFloat("shineFactor", texModel->getModelTex()->getShineFactor());
	shader->setFloat("useFakeLight", texModel->getModelTex()->useFakeLight);
}

void EntityRenderer::unbindTexturedModel() {
	enableBackCulling();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void EntityRenderer::prepareEntity(Entity & entity) {
	glm::mat4 modelMat = Maths::createModelMatrix(entity.position, entity.rotX, entity.rotY, entity.rotZ, entity.scale);
	shader->setMat4("modelMatrix", modelMat);
}
