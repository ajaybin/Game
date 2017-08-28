#include "StaticShader.h"

const char* StaticShader::fragmentShaderSourceIncl = ""
#include "shaderEntity.frag"
;

const char* StaticShader::vertexShaderSourceIncl = ""
#include "shaderEntity.vert"
;

StaticShader::StaticShader(const char * vertexShaderSource, const char * fragmentShaderSource) : ShaderProgram(vertexShaderSource, fragmentShaderSource) {
}
