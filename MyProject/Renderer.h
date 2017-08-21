#ifndef RENDERER_H
#define RENDERER_H
#include <RawModel.h>
#include <glad\glad.h>
#include <TexturedModel.h>
class Renderer {
public:
	void prepare();
	void render(TexturedModel texModel);
};
#endif
