#version 410 core
layout(location=0) in vec3 in_Position;
layout(location=1) in vec2 in_TexCoord;
uniform mat4 viewMat = mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,-3,1);
uniform mat4 projMat = mat4(1.299038,0,0,0, 0,1.732051,0,0, 0,0,-1.002002,-1.0, 0,0,-0.2002,0);
uniform mat4 modelMat = mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
out vec2 texCoord;
void main(void) {
	texCoord = in_TexCoord;
	vec4 worldPos = modelMat*vec4(in_Position, 1.0);
	gl_Position= projMat*viewMat*worldPos;
}