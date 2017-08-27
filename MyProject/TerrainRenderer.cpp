#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer(TerrainShader * shader) {
	this->shader = shader;
}

void TerrainRenderer::render(std::vector<Terrain> &terrains) {
	for (Terrain terrain : terrains) {
		prepareTerrain(&terrain);
		prepareMatrix(&terrain);
		glDrawElements(GL_TRIANGLES, terrain.getRawModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
		unbindTexturedModel();
	}
}

void TerrainRenderer::prepareTerrain(Terrain *terrain) {
	RawModel *model = terrain->getRawModel();
	glBindVertexArray(model->getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	for (unsigned int i = 0; i < terrain->getModelTex()->getNumTextures(); i++) {
		shader->setInt(("textureSampler" + std::to_string(i)).c_str(), i);
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, terrain->getModelTex()->getTexture(i));
	}
	shader->setFloat("reflectivity", terrain->getModelTex()->getReflectivity());
	shader->setFloat("shineFactor", terrain->getModelTex()->getShineFactor());
}

void TerrainRenderer::unbindTexturedModel() {
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void TerrainRenderer::prepareMatrix(Terrain *terrain) {
	glm::mat4 modelMat = Maths::createModelMatrix(glm::vec3(terrain->getX(), 0.0f, terrain->getZ()), 0.0f, 0.0f, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	shader->setMat4("modelMatrix", modelMat);
}