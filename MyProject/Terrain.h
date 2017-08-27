#pragma once
#include <Loader.h>
#include <ModelTex.h>
class Terrain {
	float SIZE;
	int VERTEX_COUNT;

	float x, z;

	RawModel model;
	ModelTex *modelTex;
public:
	Terrain(int tileX, int tileZ, Loader *loader, ModelTex *modelTex);
	RawModel generateTerrain(Loader *loader);
	RawModel* getRawModel();
	ModelTex* getModelTex();
	float getX();
	float getZ();
};