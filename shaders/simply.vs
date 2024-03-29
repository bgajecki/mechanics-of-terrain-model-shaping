#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoordinates;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 textureCoords;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	textureCoords = textureCoordinates;
}
