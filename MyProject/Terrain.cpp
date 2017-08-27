#include "Terrain.h"

Terrain::Terrain(int tileX, int tileZ, Loader * loader, ModelTex * modelTex) {
	this->SIZE = 800;
	this->VERTEX_COUNT = 128;
	this->modelTex = modelTex;
	this->x = tileX * SIZE;
	this->z = tileZ * SIZE;
	this->model = generateTerrain(loader);
}

RawModel Terrain::generateTerrain(Loader * loader) {
	std::vector<float> vertices;
	std::vector<float> texCoords;
	std::vector<float> normals;
	std::vector<int> indices;
	for (int x = 0; x < VERTEX_COUNT; x++) {
		for (int z = 0; z < VERTEX_COUNT; z++) {
			vertices.push_back((float)x * SIZE / ((float)VERTEX_COUNT - 1));
			vertices.push_back(0.0f);
			vertices.push_back((float)z * SIZE / ((float)VERTEX_COUNT - 1));
			normals.push_back(0.0f);
			normals.push_back(1.0f);
			normals.push_back(0.0f);
			texCoords.push_back((float)x * 1.0f / (float)VERTEX_COUNT);
			texCoords.push_back((float)z * 1.0f / (float)VERTEX_COUNT);
		}
	}
	for (int x = 0; x < VERTEX_COUNT-1; x++) {
		for (int z = 0; z < VERTEX_COUNT-1; z++) {
			int topLeft = (x * VERTEX_COUNT) + z;
			int bottomLeft = topLeft + 1;
			int topRight = ((x + 1) * VERTEX_COUNT) + z;
			int bottomRight = topRight + 1;
			indices.push_back(topLeft);
			indices.push_back(bottomLeft);
			indices.push_back(bottomRight);
			indices.push_back(topLeft);
			indices.push_back(bottomRight);
			indices.push_back(topRight);
		}
	}
	return loader->loadObjIntoVAO(vertices, texCoords, normals, indices);
}

RawModel * Terrain::getRawModel() {
	return &model;
}

ModelTex * Terrain::getModelTex() {
	return modelTex;
}

float Terrain::getX() {
	return x;
}

float Terrain::getZ() {
	return z;
}
