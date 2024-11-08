#version 410 core

layout(location=0) in vec3 in_Position;
uniform mat3 tf;

void main(void)
{
	vec2 p2 = in_Position.xy;
	vec3 p = tf*vec3(p2, 1.0);
	p2 = p.xy;
	gl_Position= vec4(p2, 0, 1);
}

