#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoordinates;

out vec2 textureCoords;
out vec3 FragNormal;

void main()
{
	gl_Position = vec4(position, 1.0);
	textureCoords = textureCoordinates;
	FragNormal = normal;
}
