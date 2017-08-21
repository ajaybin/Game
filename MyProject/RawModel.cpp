#include <RawModel.h>

RawModel::RawModel(unsigned int VAO, unsigned int vertexCount) {
	this->VAO = VAO;
	this->vertexCount = vertexCount;
}

unsigned int RawModel::getVertexCount() {
	return vertexCount;
}

unsigned int RawModel::getVAO() {
	return VAO;
}