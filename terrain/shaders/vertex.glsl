#version 450 core

layout (location=0) in vec3 vVertex;
layout (location=1) in vec3 vNormal;
layout (location=2) in vec2 vTexCoord;

out vec2 texCoord;
out vec3 worldPos;
out vec3 normal;
uniform mat4 mvpMatrix;

void main(void)
{
	texCoord = vTexCoord;
	worldPos = vVertex;
	normal = vNormal;
	gl_Position = mvpMatrix*vec4(vVertex,1);
}
