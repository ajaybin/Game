R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

out vec2 passTexCoords;
out vec3 surfaceNormal;
out vec3 lightVector;
out vec3 toCameraVector;
out float visibility;

const float density = 0.0075;
const float gradient = 5.0;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform float useFakeLight;

void main()
{
    vec4 vertexWorldPosition = modelMatrix * vec4(aPos, 1.0);
	vec4 positionFromCam = viewMatrix * vertexWorldPosition;
    gl_Position = projectionMatrix * positionFromCam;
	passTexCoords = texCoords;

	vec3 actualNormal = normal;
	if (useFakeLight == 1.0f) {
	  actualNormal = vec3(0.0,1.0,0.0);
	}

	mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
	surfaceNormal = normalize(normalMatrix * actualNormal);
	lightVector = normalize(lightPosition - vertexWorldPosition.xyz);
	toCameraVector = normalize(cameraPosition - vertexWorldPosition.xyz);

	float distance = length(positionFromCam.xyz);
	visibility = exp(-pow((distance * density), gradient));
	visibility = clamp(visibility, 0, 1);
}
)"