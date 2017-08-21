#include "StaticShader.h"

const char* StaticShader::fragmentShaderSourceIncl =
#include "shader.frag"
;

const char* StaticShader::vertexShaderSourceIncl =
#include "shader.vert"
;

StaticShader::StaticShader(const char * vertexShaderSource, const char * fragmentShaderSource) : ShaderProgram(vertexShaderSource, fragmentShaderSource) {
}
