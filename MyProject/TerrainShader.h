#pragma once
#include <ShaderProgram.h>
class TerrainShader : public ShaderProgram {
	static const char* vertexShaderSourceIncl;
	static const char* fragmentShaderSourceIncl;
public:
	TerrainShader(const char * vertexShaderSource = vertexShaderSourceIncl,
		const char * fragmentShaderSource = fragmentShaderSourceIncl);
};


