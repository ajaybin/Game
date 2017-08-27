#pragma once
#include <EntityRenderer.h>
#include <TerrainRenderer.h>
using namespace std;
class MasterRenderer {
	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 100.0f;

	StaticShader *shader;
	EntityRenderer *entityRenderer;

	TerrainRenderer *terrainRenderer;
	TerrainShader *terrainShader;

	std::map<TexturedModel*, std::vector<Entity>> *entities;
	std::vector<Terrain> terrains;

public:
	MasterRenderer();
	void prepare();
	void cleanUp();
	void render(Camera * camera, Light *light);
	void addEntity(Entity &entity);
	void addTerrain(Terrain &terrain);
};
