#include <Loader.h>

using namespace std;

unsigned int Loader::createVAO() {
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	vaoQ.push_back(VAO);
	glBindVertexArray(VAO);
	return VAO;
}

void Loader::unbindVAO() {
	glBindVertexArray(0);
}

void Loader::storeData(unsigned int attributePosition, unsigned int size, std::vector<float> data) {
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	vboQ.push_back(VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*data.capacity(), &data.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(attributePosition, size, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attributePosition);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(std::vector<int> indices) {
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	vboQ.push_back(VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.capacity(), &indices.front(), GL_STATIC_DRAW);
}

void Loader::unbindIndicesBuffer() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Loader::cleanUp() {
	for (std::deque<int>::iterator it = vaoQ.begin(); it != vaoQ.end(); it++) {
		unsigned int VAO = *it;
		glDeleteVertexArrays(1, &VAO);
	}
	for (std::deque<int>::iterator it = vboQ.begin(); it != vboQ.end(); it++) {
		unsigned int VBO = *it;
		glDeleteBuffers(1, &VBO);
	}
	for (std::deque<int>::iterator it = textureQ.begin(); it != textureQ.end(); it++) {
		unsigned int texture = *it;
		glDeleteTextures(1, &texture);
	}
}

unsigned int Loader::loadTexture(const char *fileName) {
	int width, height, nrChannels;
	unsigned int texture;
	unsigned char *data = stbi_load(fileName, &width, &height, &nrChannels, 0);
	glGenTextures(1, &texture);
	textureQ.push_back(texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture from file" << fileName << std::endl;
	}
	stbi_image_free(data);
	return texture;
}

RawModel Loader::loadObjIntoVAO(std::vector<float> vertices, std::vector<float> texCoords, std::vector<int> indices) {
	unsigned int VAO = createVAO();
	bindIndicesBuffer(indices);
	RawModel model (VAO, (int)indices.size());
	storeData(0, 3, vertices);
	storeData(1, 2, texCoords);
	unbindVAO();
	unbindIndicesBuffer();
	return model;
}