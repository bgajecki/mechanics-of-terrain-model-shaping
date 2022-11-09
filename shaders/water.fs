#version 460 core

layout(location = 0) out vec4 diffuseColor;

void main()
{
	const vec4 waterColor = vec4(0.0, 0.0, 1.0, 1.0);
	diffuseColor = waterColor;
}