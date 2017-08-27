#ifndef RAWMODEL_H
#define RAWMODEL_H
class RawModel {
	unsigned int VAO;
	unsigned int vertexCount;
public:
	RawModel();
	RawModel(unsigned int VAO, unsigned int vertexCount);
	unsigned int getVAO();
	unsigned int getVertexCount();
};
#endif
