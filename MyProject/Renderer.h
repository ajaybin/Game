#ifndef RENDERER_H
#define RENDERER_H
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
class Renderer {
	StaticShader *shader;

	int width, height;
	float fov;
public:
	Renderer(StaticShader *shader);
	void prepare();
	void render(std::map<TexturedModel*, std::vector<Entity>> *entites);
	void prepareTexturedModel(TexturedModel *model);
	void unbindTexturedModel();
	void prepareEntity(Entity &entity);
	void setAspect(int width, int height);
};
#endif
