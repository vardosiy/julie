#version 330 core
precision mediump float;

out vec4 o_color;

uniform vec4 u_color;

void main()
{
	o_color = u_color;
}
