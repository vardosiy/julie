precision mediump float;

#define TEXTURES_COUNT 4

in vec2 v_uv;
in vec2 v_uvTiling;
in vec3 v_posW;

// 0 - mask
// 1 - grass
// 2 - dirt
// 3 - rock
uniform sampler2D u_texture2D[TEXTURES_COUNT];

uniform float u_fogStart;
uniform float u_fogRange;
uniform vec4 u_fogColor;
uniform vec3 u_camPosition;

void main()
{
	vec4 grass, dirt, rock, mask, terrain;
	
	mask	= texture2D(u_texture2D[0], v_uv);
	grass	= texture2D(u_texture2D[1], v_uvTiling);
	dirt	= texture2D(u_texture2D[2], v_uvTiling);
	rock	= texture2D(u_texture2D[3], v_uvTiling);

	terrain = (grass * mask.x + dirt * mask.y + rock * mask.z) / (mask.x + mask.y + mask.z);

	float distance = distance(u_camPosition, v_posW);
	float factor = clamp((distance - u_fogStart) / u_fogRange, 0.0, 1.0);

	vec4 result = mix(terrain, u_fogColor, factor);
	result.a = 1.0;

	gl_FragColor = result;
}
