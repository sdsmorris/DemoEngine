#version 330 core

//TODO: billboarding

layout (location = 0) in vec3 in_Pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	//3D vao
	//gl_Position = projection * view * model * vec4(in_Pos, 1.0);
	//2D vao
	gl_Position = projection * view * model * vec4(in_Pos, 1.0);


}