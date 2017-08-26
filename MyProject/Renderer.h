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
using namespace std;
class Renderer {
	StaticShader shader;
	Camera *camera;
	Light *light;

	int width, height;
	float fov;
public:
	Renderer(StaticShader &shader, Camera *camera, Light *light);
	void prepare();
	void render(Entity &entity);
	void setAspect(int width, int height);
};
#endif
