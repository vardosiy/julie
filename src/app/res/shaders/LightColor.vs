#version 330 core

layout (location = 0) in vec3 a_posL;
layout (location = 2) in vec3 a_normL;

out vec3 v_posW;
out vec3 v_normW;

uniform mat4 u_W;
uniform mat4 u_WVP;

void main()
{
	gl_Position = u_WVP * vec4(a_posL, 1.0);

	v_posW = vec3(u_W * vec4(a_posL, 1.0));
	v_normW = vec3(u_W * vec4(a_normL, 0.0));
}
