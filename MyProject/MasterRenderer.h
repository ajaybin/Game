#pragma once
#include <Renderer.h>

using namespace std;
class MasterRenderer {
	StaticShader *shader;
	Renderer *renderer;

	std::map<TexturedModel*, std::vector<Entity>> *entities;

public:
	MasterRenderer();
	void cleanUp();
	void render(Camera * camera, Light *light);
	void addEntity(Entity &entity);
};
