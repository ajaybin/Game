#ifndef RENDERER_H
#define RENDERER_H
#include <RawModel.h>
#include <glad\glad.h>
#include <TexturedModel.h>
#include <Entity.h>
#include <StaticShader.h>
class Renderer {
	StaticShader shader;
public:
	Renderer(StaticShader shader);
	void prepare();
	void render(Entity entity);
};
#endif
