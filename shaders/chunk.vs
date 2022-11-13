#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 color;

uniform mat4 mvp;
uniform vec3 viewPosition;

out vec3 FragPosition;
out vec3 FragNormal;
out vec4 FragColor;

void main()
{
	gl_Position = mvp * vec4(position, 1.0);

	FragPosition = position;
	FragNormal = normal;
	FragColor = color;
}
