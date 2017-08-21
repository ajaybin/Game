#ifndef STATIC_SHADER_H
#define STATIC_SHADER_H
#include <ShaderProgram.h>
class StaticShader : public ShaderProgram {
	static const char* vertexShaderSourceIncl;
	static const char* fragmentShaderSourceIncl;
public:
	StaticShader(const char * vertexShaderSource = vertexShaderSourceIncl, 
		         const char * fragmentShaderSource = fragmentShaderSourceIncl);
};
#endif
