#ifndef LOADER_H
#define LOADER_H
#include <glad\glad.h>
#include <stb_image.h>
#include <RawModel.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <string>
#include <sstream>
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
	std::vector<std::string> split(const std::string &s, char delim);
	void processVertex(std::vector<std::string> &vertex, std::vector<glm::vec2> &textureVector, std::vector<glm::vec3> &normalVector, 
		std::vector<int> &indexArray, float *textureArray, float *normalArray);
public:
	RawModel loadObjIntoVAO(std::vector<float> vertices, std::vector<float> texCoords, 
		std::vector<float> normals, std::vector<int> indices);
	void cleanUp();
	unsigned int loadTexture(const char *fileName);
	RawModel loadObjFromFile(const char *fileName);

};
#endif
