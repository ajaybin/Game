#include "TerrainShader.h"

const char* TerrainShader::fragmentShaderSourceIncl = ""
#include "shaderTerrain.frag"
;

const char* TerrainShader::vertexShaderSourceIncl = ""
#include "shaderTerrain.vert"
;

TerrainShader::TerrainShader(const char * vertexShaderSource, const char * fragmentShaderSource) : ShaderProgram(vertexShaderSource, fragmentShaderSource) {
}