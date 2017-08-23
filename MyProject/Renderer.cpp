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
	glm::mat4 modelMat = Maths::createModelMatrix(entity.position, entity.rotX, entity.rotY, entity.rotZ, entity.scale);
	shader.setMat4("modelMatrix", modelMat);
	glm::mat4 projectionMatrix = Maths::createProjectionMatrix(45.0f, (float)this->width / (float)this->height, 0.1f, 100.0f);
	shader.setMat4("projectionMatrix", projectionMatrix);
	glm::mat4 viewMatrix = Maths::createViewMatrix(glm::vec3(0.0f, 0.0f, -3.0f));
	shader.setMat4("viewMatrix", viewMatrix);
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
