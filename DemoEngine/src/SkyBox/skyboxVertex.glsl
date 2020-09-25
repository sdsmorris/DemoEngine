#version 330 core

in vec3 position;

out vec3 textureCoords;

//FOG
const float density = 0.35;
const float gradient = 5.0;
out float visibility;

uniform mat4 projection;
uniform mat4 view;

void main(void)
{
	gl_Position = projection * view * vec4(position, 1.0);
	textureCoords = position;    
    
    //FOG
    vec4 posRelativeToCam = view * vec4(position, 1.0);
    float distance = length(posRelativeToCam.xyz);
    visibility = exp(-pow((distance*density), gradient));
    visibility = clamp(visibility, 0.0, 1.0);
}