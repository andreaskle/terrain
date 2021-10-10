#version 450 core
in vec3 worldPos[];
in vec3 normal[];
in vec2 texCoord[];

out vec2 tesTexCoords[];
out vec3 tesWorldPos[];
out vec3 tesNormal[];
layout(vertices = 3) out;
uniform float tessFactor;

void main(void) 
{
    tesWorldPos[gl_InvocationID] = worldPos[gl_InvocationID];
    tesTexCoords[gl_InvocationID] = texCoord[gl_InvocationID];
      
    if (gl_InvocationID == 0) {
        gl_TessLevelInner[0] = tessFactor;
        gl_TessLevelInner[1] = tessFactor;
        gl_TessLevelOuter[0] = tessFactor;
        gl_TessLevelOuter[1] = tessFactor;
        gl_TessLevelOuter[2] = tessFactor;
    }
    
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    tesNormal[gl_InvocationID] = normal[gl_InvocationID];
    
}
