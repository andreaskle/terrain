#version 450 core
layout (triangles) in;
in vec3 tesWorldPos[];
in vec2 tesTexCoords[];
in vec3 tesNormal[];
uniform sampler2D bumpMap;
uniform mat4 mvpMatrix;

out vec2 texCoord;
out vec3 normal;
out vec3 worldPos;

vec3 interpolate3D(vec3 v1, vec3 v2, vec3 v3){
    
    return v1*gl_TessCoord.x+v2*gl_TessCoord.y+v3*gl_TessCoord.z;

}
vec2 interpolate2D(vec2 v1, vec2 v2, vec2 v3){
    return v1*gl_TessCoord.x+v2*gl_TessCoord.y+v3*gl_TessCoord.z;
}

vec3 gradient(vec2 texCoord){
    float eps = 0.0001;
    float x = texture(bumpMap, texCoord+vec2(eps,0)).x - texture(bumpMap, texCoord-vec2(eps,0)).x;
    float z = texture(bumpMap, texCoord+vec2(0,eps)).x - texture(bumpMap, texCoord-vec2(0, eps)).x;
    return normalize(vec3(x, 2*eps, z));
}
void main(void)
{
    texCoord = interpolate2D(tesTexCoords[0], tesTexCoords[1], tesTexCoords[2]);

    float height = texture(bumpMap, texCoord).x * 10;
    normal = interpolate3D(tesNormal[0], tesNormal[1],tesNormal[2]);
    worldPos = interpolate3D(tesWorldPos[0], tesWorldPos[1], tesWorldPos[2]) + normal * height;
    normal = gradient(texCoord);
    gl_Position = mvpMatrix * vec4(worldPos,1);
    
}
