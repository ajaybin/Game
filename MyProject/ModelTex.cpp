#include "ModelTex.h"

ModelTex::ModelTex(float shineFactor, float reflectivity) {
	this->shineFactor = shineFactor;
	this->reflectivity = reflectivity;
}

void ModelTex::addTexture(unsigned int texture) {
	this->texture.push_back(texture);
}

unsigned int ModelTex::getNumTextures() {
	return (unsigned int)texture.size();
}

unsigned int ModelTex::getTexture(unsigned int index)
{
	return texture.at(index);
}

float ModelTex::getReflectivity() {
	return reflectivity;
}

float ModelTex::getShineFactor() {
	return shineFactor;
}
