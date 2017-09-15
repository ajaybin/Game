#include "BaseRenderer.h"

void BaseRenderer::enableBackCulling() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void BaseRenderer::disableBackCulling() {
	glDisable(GL_CULL_FACE);
}

BaseRenderer::BaseRenderer() {
}
