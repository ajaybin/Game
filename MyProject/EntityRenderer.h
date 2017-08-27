#ifndef ENTITYRENDERER_H
#define ENTITYRENDERER_H
#include <string>
#include <glad\glad.h>
#include <RawModel.h>
#include <TexturedModel.h>
#include <Entity.h>
#include <Maths.h>
#include <StaticShader.h>
#include <Camera.h>
#include <Light.h>
#include <map>
using namespace std;
class EntityRenderer {
	StaticShader *shader;
public:
	EntityRenderer(StaticShader *shader);
	void render(std::map<TexturedModel*, std::vector<Entity>> *entites);
	void prepareTexturedModel(TexturedModel *model);
	void unbindTexturedModel();
	void prepareEntity(Entity &entity);
};
#endif
