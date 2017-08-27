#pragma once
#include <TerrainShader.h>
#include <Terrain.h>
#include <Maths.h>
class TerrainRenderer {
	TerrainShader *shader;

public:
	TerrainRenderer(TerrainShader *shader);
	void render(std::vector<Terrain> &terrains);
	void prepareTerrain(Terrain *terrain);
	void unbindTexturedModel();
	void prepareMatrix(Terrain *terrain);
};
