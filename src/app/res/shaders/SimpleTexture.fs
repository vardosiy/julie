#version 330 core
precision mediump float;

in vec2 v_uv;
out vec4 o_color;

uniform sampler2D u_texture2D;

void main()
{
	o_color = texture2D(u_texture2D, v_uv);
}
