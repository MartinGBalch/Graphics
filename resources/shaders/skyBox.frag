#version 450 core

layout (location = 3) uniform samplerCube skybox;
out vec4 FragColor;

in vec3 TexCoords;



void main()
{    
    FragColor = texture(skybox, TexCoords);
}