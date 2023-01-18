#version 460 core

layout(location = 0) out vec4 color;

uniform sampler2D textureSampler;

in vec2 textureCoords;

void main()
{
	color = texture(textureSampler, textureCoords);
}