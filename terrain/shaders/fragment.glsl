#version 450 core
out vec4 fragColor;
in vec2 texCoord;
in vec3 normal;
in vec3 worldPos;

vec3 interpolateColor(float y){

	vec3 blue = vec3(0.02,0.15, 0.21);
	vec3 green = vec3(0.27,0.38,0.19);
	vec3 brown = vec3(0.47,0.4,0.33);
	vec3 grey = vec3(0.75,0.74,0.71);
	vec3 ice = vec3(0.75,0.74,0.71);
	vec3 color = blue;

	color = mix(blue, green, smoothstep(0,0.1f, y));
	color = mix(color, brown, smoothstep(0.1f,3, y));
	color = mix(color, grey, smoothstep(2.5f,4, y));
	color = mix(color, ice, smoothstep(4,6, y));
	return color;
}

void main()
{
	float nDotL = dot(normalize(normal),normalize(vec3(0,1,-1)));
	fragColor = vec4(interpolateColor(worldPos.y)*nDotL,1);
} 

