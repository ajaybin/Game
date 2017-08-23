R"(
#version 330 core
in vec2 passTexCoords;

out vec4 fragColor;

uniform sampler2D textureSampler0;
uniform sampler2D textureSampler1;

void main()
{
    fragColor = mix(texture(textureSampler0, passTexCoords), texture(textureSampler1, passTexCoords), 0.5);
}
)"