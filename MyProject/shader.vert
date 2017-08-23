R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoords;

out vec2 passTexCoords;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
void main()
{
    gl_Position = projectionMatrix * modelMatrix * vec4(aPos, 1.0);
	passTexCoords = texCoords;
}
)"