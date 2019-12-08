#version 330 core
precision mediump float;

in vec2 v_uv;

uniform sampler2D u_texture2D[2];

void main(void)
{
	vec4 color = texture2D(u_texture2D[0], v_uv);
	vec4 blur = texture2D(u_texture2D[1], v_uv);

	gl_FragColor = color + 1.6 * blur;
}
