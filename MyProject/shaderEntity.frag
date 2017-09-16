R"(
#version 330 core
in vec2 passTexCoords;
in vec3 surfaceNormal;
in vec3 lightVector;
in vec3 toCameraVector;
in float visibility;

out vec4 fragColor;

uniform sampler2D textureSampler0;
uniform sampler2D textureSampler1;
uniform vec3 lightColour;
uniform float reflectivity;
uniform float shineFactor;
uniform vec3 skyColour;
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
	vec4 texColour = texture(textureSampler0, passTexCoords);
	if(texColour.a < 0.5) {
	  discard;
	}
    fragColor = vec4(diffuse + ambient, 1.0f) * texColour + vec4(specular, 1.0f);
	fragColor = mix(vec4(skyColour,1.0),fragColor, visibility);
}
)"