in vec3 a_posL;
in vec2 a_uv;

out vec2 v_uv;

uniform mat4 u_WVP;

void main()
{
	gl_Position = u_WVP * vec4(a_posL, 1.0);

	v_uv = a_uv;
}
