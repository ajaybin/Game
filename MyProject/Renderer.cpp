#include <Renderer.h>

void Renderer::prepare() {
	glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render(TexturedModel texModel) {
	RawModel model = texModel.getRawModel();
	glBindVertexArray(model.getVAO());
	for (unsigned int i = 0; i < texModel.getModelTex().getNumTextures(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texModel.getModelTex().getTexture(i));
	}
	glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}