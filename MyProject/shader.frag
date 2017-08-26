R"(
#version 330 core
in vec2 passTexCoords;
in vec3 surfaceNormal;
in vec3 lightVector;

out vec4 fragColor;

uniform sampler2D textureSampler0;
uniform sampler2D textureSampler1;
uniform vec3 lightColour;

void main()
{
    float normalDotLight = dot(surfaceNormal, lightVector);
	float brightness = max(normalDotLight, 0.1);
	vec3 diffuse = brightness * lightColour;

    fragColor = vec4(diffuse, 1.0f) * texture(textureSampler0, passTexCoords);
}
)"