#include "ModelTex.h"

ModelTex::ModelTex(int texture) {
	this->texture = texture;
}

unsigned int ModelTex::getTexture()
{
	return texture;
}
