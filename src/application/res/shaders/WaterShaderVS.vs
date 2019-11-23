attribute vec3 a_posL;
attribute vec2 a_uv;
attribute vec3 a_normL;
attribute vec3 a_bitangentL;
attribute vec3 a_tangentL;

varying vec3 v_posW;
varying vec2 v_uv;
varying vec2 v_uvTiling;
varying vec3 v_normalW;
varying vec3 v_bitangentW;
varying vec3 v_tangentW;

uniform mat4 u_W;
uniform mat4 u_WVP;

uniform float u_tilingFactor;

void main()
{
	gl_Position = u_WVP * vec4(a_posL, 1.0);
	
	v_posW = (u_W * vec4(a_posL, 1.0)).xyz;
	v_uvTiling = a_uv * u_tilingFactor;
	v_uv = a_uv;

	v_normalW = normalize( (u_W * vec4(a_normL, 0.0)).xyz );
	v_tangentW = normalize( (u_W * vec4(a_tangentL, 0.0)).xyz );
	v_bitangentW = normalize( (u_W * vec4(a_bitangentL, 0.0)).xyz );
}
