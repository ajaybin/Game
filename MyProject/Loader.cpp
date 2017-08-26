#include "Loader.h"

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

std::vector<std::string> Loader::split(const std::string & s, char delim) {
	std::vector<std::string> stringVector;
	std::stringstream ss;
	std::string str;
	ss.str(s);
	while (std::getline(ss, str, delim)) {
		stringVector.push_back(str);
	}
	return stringVector;
}

void Loader::processVertex(std::vector<std::string> vertex, std::vector<glm::vec2> textureVector, std::vector<glm::vec3> normalVector, 
	std::vector<int> &indexArray, float * textureArray, float * normalArray) {
	int index = std::stoi(vertex[0]) - 1;
	indexArray.push_back(index);
	glm::vec2 currentTexture = textureVector.at(std::stoi(vertex[1]) - 1);
	textureArray[index * 2] = currentTexture.x;
	textureArray[index * 2 + 1] = 1- currentTexture.y;
	glm::vec3 currentNormal = normalVector.at(std::stoi(vertex[2]) - 1);
	normalArray[index * 3] = currentNormal.x;
	normalArray[index * 3 + 1] = currentNormal.y;
	normalArray[index * 3 + 2] = currentNormal.z;
}

void Loader::cleanUp() {
	for (unsigned int VAO : vaoQ) {
		glDeleteVertexArrays(1, &VAO);
	}
	for (unsigned int VBO : vboQ) {
		glDeleteBuffers(1, &VBO);
	}
	for (unsigned int texture : textureQ) {
		glDeleteTextures(1, &texture);
	}
}

unsigned int Loader::loadTexture(const char *fileName) {
	int width, height, nrChannels;
	unsigned int texture;
	unsigned char *data = stbi_load(fileName, &width, &height, &nrChannels, 3);
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
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
	return texture;
}

RawModel Loader::loadObjFromFile(const char * fileName) {
	std::vector<glm::vec3> vertexVector;
	std::vector<glm::vec2> textureVector;
	std::vector<glm::vec3> normalVector;
	std::vector<int> indexArray;

	std::ifstream ifs(fileName);
	if (ifs.fail()) {
		std::cerr << "Failed to open OBJ file" << fileName << std::endl;
	}
	std::string line;
	while(std::getline(ifs, line)) {
		std::istringstream iss(line);
		if (line.substr(0, 2) == "v ") {
			glm::vec3 vertex;
			std::string v;
			if (!(iss >> v >> vertex.x >> vertex.y >> vertex.z)) {
				std::cerr << "Something went wrong during obj vertex parsing" << std::endl;
			}
			vertexVector.push_back(vertex);
		} 
		else if (line.substr(0, 2) == "vt") {
			glm::vec2 texCoord;
			std::string vt;
			if (!(iss >> vt >> texCoord.x >> texCoord.y)) {
				std::cerr << "Something went wrong during obj texture parsing" << std::endl;
			}
			textureVector.push_back(texCoord);
		} 
		else if (line.substr(0, 2) == "vn") {
			glm::vec3 normal;
			std::string vn;
			if (!(iss >> vn >> normal.x >> normal.y >> normal.z)) {
				std::cerr << "Something went wrong during obj normal parsing" << std::endl;
			}
			normalVector.push_back(normal);
		}
		else if (line.substr(0,2) == "f ") {
			break;
		}
		else {
			continue;
		}
	}

	float *textureArray = new float[vertexVector.size() * 2];
	float *normalArray = new float[vertexVector.size() * 3];
	do {
		std::istringstream iss(line);
		if (line.substr(0, 2) == "f ") {
			std::string f, vertex1, vertex2, vertex3;
			if (!(iss >> f >> vertex1 >> vertex2 >> vertex3)) {
				std::cerr << "Something went wrong during obj faces parsing" << std::endl;
			}
			processVertex(split(vertex1, '/'), textureVector, normalVector, indexArray, textureArray, normalArray);
			processVertex(split(vertex2, '/'), textureVector, normalVector, indexArray, textureArray, normalArray);
			processVertex(split(vertex3, '/'), textureVector, normalVector, indexArray, textureArray, normalArray);
		}
		else {
			continue;
		}
	} while (std::getline(ifs, line));

	std::vector<float> vertices;
	std::vector<float> texCoords;
	std::vector<float> normals;
	for (glm::vec3 vertex : vertexVector) {
		vertices.push_back(vertex.x);
		vertices.push_back(vertex.y);
		vertices.push_back(vertex.z);
	}
	for (int i = 0; i < vertexVector.size() * 2; i++) {
		texCoords.push_back(textureArray[i]);
	}
	for (int i = 0; i < vertexVector.size() * 3; i++) {
		normals.push_back(normalArray[i]);
	}
	delete[] textureArray;
	delete[] normalArray;

	return loadObjIntoVAO(vertices, texCoords, normals, indexArray);
}

RawModel Loader::loadObjIntoVAO(std::vector<float> vertices, std::vector<float> texCoords, 
	std::vector<float> normals, std::vector<int> indices) {
	unsigned int VAO = createVAO();
	bindIndicesBuffer(indices);
	RawModel model (VAO, (int)indices.size());
	storeData(0, 3, vertices);
	storeData(1, 2, texCoords);
	storeData(2, 3, normals);
	unbindVAO();
	unbindIndicesBuffer();
	return model;
}