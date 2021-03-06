#version 450
layout (location = 0) in vec4 position;
layout (location = 2) in vec2 uv;

layout (location = 0) uniform mat4 model;


out vec2 vUV;

void main ()
{
	gl_Position = model * position;
	vUV = uv;
}
