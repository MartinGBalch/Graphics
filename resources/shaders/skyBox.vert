#version 450 core
layout (location = 0) in vec4 position;

layout (location = 0) uniform mat4 projection;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 model;
out vec3 TexCoords;

void main()
{
    TexCoords = (position).xyz;
    gl_Position = projection * view * model * position; 
}  