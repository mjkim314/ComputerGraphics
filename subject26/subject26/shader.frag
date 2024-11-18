#version 150 core

out vec4 out_Color;
in vec3 normal;
uniform vec3 color = vec3(1, 0.5, 0);
uniform vec3 lightColor = vec3(1, 1, 1);
uniform vec3 lightPos = vec3(10, 20, 10);
uniform vec3 diffuseColor;
uniform float shininess;
uniform vec3 cameraPos;
in vec3 worldCoord;

void main(void)
{
	vec3 L = normalize(lightPos - worldCoord);
	vec3 N = normalize(normal);
	vec3 C = color*max(0, dot(N, L))*lightColor;
	out_Color = vec4(C, 1.0);
}
