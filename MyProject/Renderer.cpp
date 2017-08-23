#include <Renderer.h>
#include <Maths.h>
Renderer::Renderer(StaticShader shader, int width, int height) : shader(shader) {
	this->width = width;
	this->height = height;
}
void Renderer::prepare() {
	glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render(Entity entity) {
	TexturedModel texModel = entity.getModel();
	RawModel model = texModel.getRawModel();
	glBindVertexArray(model.getVAO());
	shader.setInt("textureSampler0", 0);
	shader.setInt("textureSampler1", 1);
	glm::mat4 modelMat = Maths::createModelMatrix(entity.position, entity.rotX, entity.rotY, entity.rotZ, entity.scale);
	shader.setMat4("modelMatrix", modelMat);
	glm::mat4 projectionMatrix = Maths::createProjectionMatrix(45.0f, (float)this->width / (float)this->height, 1.0f, 100.0f);
	shader.setMat4("projectionMatrix", projectionMatrix);
	for (unsigned int i = 0; i < texModel.getModelTex().getNumTextures(); i++) {
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
