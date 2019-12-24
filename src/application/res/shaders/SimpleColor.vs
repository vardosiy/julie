#version 330 core

layout (location = 0) in vec3 a_posL;

uniform mat4 u_WVP;

void main()
{
	//gl_Position = u_WVP * vec4(a_posL, 1.0);
	gl_Position = vec4(a_posL, 1.0);
}
