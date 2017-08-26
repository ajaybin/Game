R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

out vec2 passTexCoords;
out vec3 surfaceNormal;
out vec3 lightVector;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

void main()
{
    vec4 vertexWorldPosition = modelMatrix * vec4(aPos, 1.0);
    gl_Position = projectionMatrix * viewMatrix * vertexWorldPosition;
	passTexCoords = texCoords;

	surfaceNormal = normalize((modelMatrix * vec4(normal, 0)).xyz);
	lightVector = normalize(lightPosition - vertexWorldPosition.xyz);
}
)"