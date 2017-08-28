R"(
#version 330 core
in vec2 passTexCoords;
in vec3 surfaceNormal;
in vec3 lightVector;
in vec3 toCameraVector;

out vec4 fragColor;

uniform sampler2D textureSampler0;
uniform sampler2D textureSampler1;
uniform vec3 lightColour;
uniform float reflectivity;
uniform float shineFactor;
void main()
{
    float normalDotLight = dot(surfaceNormal, lightVector);
	float brightness = max(normalDotLight, 0.0);
	float ambientStrength = 0.1;
	vec3 diffuse = brightness * lightColour;
	vec3 ambient = ambientStrength * lightColour;

	vec3 reflectVector = reflect(-lightVector, surfaceNormal);
	float spec = pow(max(dot(reflectVector, toCameraVector), 0.0), shineFactor);
	vec3 specular = spec * reflectivity * lightColour;

    fragColor = vec4(diffuse + ambient, 1.0f) * texture(textureSampler0, passTexCoords) + vec4(specular, 1.0f);
}
)"