#version 330 core
precision mediump float;

in vec2 v_uv;

uniform sampler2D u_texture2D;

void main()
{
	gl_FragColor = texture2D(u_texture2D, v_uv);
}
