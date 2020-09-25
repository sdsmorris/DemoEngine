#version 330 core

in vec3 textureCoords;
out vec4 fragColor;

//FOG
in float visibility;
uniform vec3 skyColor;
uniform bool useFog = true;

uniform samplerCube cubeMap;

void main(void)
{
	fragColor = texture(cubeMap, textureCoords);    
    //FOG
    //if (useFog)
        //fragColor = mix(vec4(skyColor, 1.0), fragColor, visibility);
}