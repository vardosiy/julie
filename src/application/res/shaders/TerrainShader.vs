in vec3 a_posL;
in vec2 a_uv;

out vec2 v_uv;
out vec2 v_uvTiling;
out vec3 v_posW;

uniform mat4 u_WVP;
uniform mat4 u_W;
uniform float u_tilingFactor;

void main()
{
	gl_Position = u_WVP * vec4(a_posL, 1.0);

	v_uv = a_uv;
	v_uvTiling.x = a_uv.x * u_tilingFactor;
	v_uvTiling.y = a_uv.y * u_tilingFactor;
	v_posW = vec3(u_W * vec4(a_posL, 1.0));
}
