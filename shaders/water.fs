#version 460 core

layout(location = 0) out vec4 color;

uniform sampler2D textureSampler;

in vec2 textureCoords;

void main()
{
	color = texture(textureSampler, textureCoords);
	color.r = 0.0;
	color.g = 0.0;
	color.b += 0.5;
	color.a = 0.8;
}