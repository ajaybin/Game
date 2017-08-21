#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include <glad/glad.h>
#include <iostream>
using namespace std;
const unsigned int LOG_SIZE = 512;

class ShaderProgram {
	unsigned int vertexShader, fragmentShader, shaderProgram;

	int createShader(GLenum type, const char * shaderSource);

public:
	ShaderProgram(const char * vertexShaderSource, const char * fragmentShaderSource);
	void start();
	void end();
};
#endif
