#version 460 core

layout(location = 0) out vec4 color;

void main()
{
	const vec4 waterColor = vec4(0.0, 0.0, 0.8, 1.0);
	color = waterColor;
}