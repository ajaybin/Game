#include "ShaderProgram.h"

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
