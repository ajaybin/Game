#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include <glad/glad.h>
#include <glm/fwd.hpp>
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
	void setBool(const char * name, bool value);
	void setInt(const char * name, int value);
	void setFloat(const char * name, float value);
	void setVec2(const char * name, const glm::vec2 &value);
	void setVec2(const char * name, float x, float y);
	void setVec3(const char * name, const glm::vec3 &value);
	void setVec3(const char * name, float x, float y, float z);
	void setVec4(const char * name, const glm::vec4 &value);
	void setVec4(const char * name, float x, float y, float z, float w);
	void setMat2(const char * name, const glm::mat2 &value);
	void setMat3(const char * name, const glm::mat3 &value);
	void setMat4(const char * name, const glm::mat4 &value);
};
#endif
