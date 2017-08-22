#include "ShaderProgram.h"
#include <glm/glm.hpp>

int ShaderProgram::createShader(GLenum type, const char * shaderSource) {
	unsigned int shader = glCreateShader(type);
	int success;
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	//check for compile errors
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[LOG_SIZE];
		glGetShaderInfoLog(shader, LOG_SIZE, NULL, infoLog);
		std::cout << "ERROR shader compilation failed\n" << infoLog << std::endl;
	}
	return shader;
}

ShaderProgram::ShaderProgram(const char * vertexShaderSource, const char * fragmentShaderSource) {
	vertexShader   = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	int success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[LOG_SIZE];
		glGetProgramInfoLog(shaderProgram, LOG_SIZE, NULL, infoLog);
		std::cout << "ERROR program link failed\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::start() {
	glUseProgram(shaderProgram);
}

void ShaderProgram::end() {
	glUseProgram(0);
}

void ShaderProgram::setBool(const char * name, bool value) {
	glUniform1i(glGetUniformLocation(shaderProgram, name), value);
}

void ShaderProgram::setInt(const char* name, int value) {
	glUniform1i(glGetUniformLocation(shaderProgram, name), value);
}

void ShaderProgram::setFloat(const char * name, float value) {
	glUniform1f(glGetUniformLocation(shaderProgram, name), value);
}

void ShaderProgram::setVec2(const char * name, const glm::vec2 &value) {
	glUniform2fv(glGetUniformLocation(shaderProgram, name), 1, &value[0]);
}

void ShaderProgram::setVec2(const char * name, float x, float y) {
	glUniform2f(glGetUniformLocation(shaderProgram, name), x, y);
}

void ShaderProgram::setVec3(const char * name, const glm::vec3 & value) {
	glUniform3fv(glGetUniformLocation(shaderProgram, name), 1, &value[0]);
}

void ShaderProgram::setVec3(const char * name, float x, float y, float z) {
	glUniform3f(glGetUniformLocation(shaderProgram, name), x, y, z);
}

void ShaderProgram::setVec4(const char * name, const glm::vec4 & value) {
	glUniform4fv(glGetUniformLocation(shaderProgram, name), 1, &value[0]);
}

void ShaderProgram::setVec4(const char * name, float x, float y, float z, float w) {
	glUniform4f(glGetUniformLocation(shaderProgram, name), x, y, z, w);
}

void ShaderProgram::setMat2(const char * name, const glm::mat2 & value) {
	glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::setMat3(const char * name, const glm::mat3 & value) {
	glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::setMat4(const char * name, const glm::mat4 & value) {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, &value[0][0]);
}
