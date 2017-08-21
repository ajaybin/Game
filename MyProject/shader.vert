R"(
#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoords;

out vec2 passTexCoords;

void main()
{
    gl_Position = vec4(aPos, 1.0);
	passTexCoords = texCoords;
}
)"