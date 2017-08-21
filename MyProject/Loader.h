#ifndef LOADER_H
#define LOADER_H
#include <glad\glad.h>
#include <RawModel.h>
#include <vector>
#include <stb_image.h>
#include <iostream>
using namespace std;

class Loader {
	std::vector<unsigned int> vaoQ;
	std::vector<unsigned int> vboQ;
	std::vector<unsigned int> textureQ;

	unsigned int createVAO();

	void unbindVAO();

	void storeData(unsigned int attributePosition, unsigned int size, std::vector<float> vertices);

	void bindIndicesBuffer(std::vector<int> indices);
	void unbindIndicesBuffer();
public:
	RawModel loadObjIntoVAO(std::vector<float> vertices, std::vector<float> texCoords, std::vector<int> indices);
	void cleanUp();
	unsigned int loadTexture(const char *fileName);

};
#endif
