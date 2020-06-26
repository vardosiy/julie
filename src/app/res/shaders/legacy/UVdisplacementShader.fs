#version 330 core
precision mediump float;

#define TEXTURES_COUNT 3

in vec2 v_uv;
out vec4 o_color;

uniform float u_time;
uniform float u_dMax;

// 0 - displacemnet map
// 1 - texture
// 2 - mask
uniform sampler2D u_texture2D[TEXTURES_COUNT];

void main()
{
	vec4 alphaValue = texture2D(u_texture2D[2], v_uv);
	if (alphaValue.r < 0.1)
		discard;

	vec2 dispMapUv = vec2(v_uv.x, v_uv.y + u_time);
	vec2 disp = texture2D(u_texture2D[0], dispMapUv).xy;

	float offsetU = (2.0 * disp.x - 1.0) * u_dMax;
	float offsetV = (2.0 * disp.y - 1.0) * u_dMax;
	vec2 newUv = v_uv + vec2(offsetU, offsetV);

	vec4 color = texture2D(u_texture2D[1], newUv);
	o_color = color * (1.0, 1.0, 1.0, alphaValue.r);
}
