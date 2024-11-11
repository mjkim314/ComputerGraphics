#version 150 core

out vec4 out_Color;
in vec3 normal;

void main(void)
{
	out_Color = vec4(normal, 1.0);
}
