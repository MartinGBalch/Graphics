#version 450

layout (location = 1) uniform sampler2D map;

out vec4 outColor;
in vec2 vUV;
void main ()
{
	outColor = texture(map, vUV);
}
