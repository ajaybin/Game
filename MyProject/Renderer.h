#ifndef RENDERER_H
#define RENDERER_H
#include <RawModel.h>
#include <glad\glad.h>
#include <TexturedModel.h>
#include <Entity.h>
#include <StaticShader.h>
#include <string>
using namespace std;
class Renderer {
	StaticShader shader;
	int width, height;
public:
	Renderer(StaticShader shader, int width, int height);
	void prepare();
	void render(Entity entity);
	void setAspect(int width, int height);
};
#endif
