#version 460 core

layout(location = 0) out vec4 diffuseColor;

uniform sampler2D textureSampler;

in vec2 textureCoords;

void main()
{
	diffuseColor = texture(textureSampler, textureCoords);
}