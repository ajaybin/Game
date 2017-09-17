R"(
#version 330 core
in vec2 passTexCoords;
in vec3 surfaceNormal;
in vec3 lightVector;
in vec3 toCameraVector;
in float visibility;

out vec4 fragColor;

uniform sampler2D textureSampler0; //Background
uniform sampler2D textureSampler1; //Red
uniform sampler2D textureSampler2; //Green
uniform sampler2D textureSampler3; //Blue
uniform sampler2D textureSampler4; //Blendmap

uniform vec3 lightColour;
uniform float reflectivity;
uniform float shineFactor;
uniform vec3 skyColour;
void main()
{
    vec4 blendMapColour = texture(textureSampler4, passTexCoords);
	float backColourValue = 1 - (blendMapColour.r + blendMapColour.g + blendMapColour.b);
	vec2 tiledTexCoords = passTexCoords * 128.0;
	vec4 backgroundTextureColour = texture(textureSampler0, tiledTexCoords) * backColourValue;
	vec4 rTexureColour = texture(textureSampler1, tiledTexCoords) * blendMapColour.r;
	vec4 gTexureColour = texture(textureSampler2, tiledTexCoords) * blendMapColour.g;
	vec4 bTexureColour = texture(textureSampler3, tiledTexCoords) * blendMapColour.b;

	vec4 totalColour = backgroundTextureColour + rTexureColour + gTexureColour + bTexureColour;

    float normalDotLight = dot(surfaceNormal, lightVector);
	float brightness = max(normalDotLight, 0.0);
	float ambientStrength = 0.2;
	vec3 diffuse = brightness * lightColour;
	vec3 ambient = ambientStrength * lightColour;

	vec3 reflectVector = reflect(-lightVector, surfaceNormal);
	float spec = pow(max(dot(reflectVector, toCameraVector), 0.0), shineFactor);
	vec3 specular = spec * reflectivity * lightColour;

    fragColor = vec4(diffuse + ambient, 1.0f) * totalColour + vec4(specular, 1.0f);
	fragColor = mix(vec4(skyColour,1.0),fragColor, visibility);
}
)"