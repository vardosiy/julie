in vec3 a_posL;
in vec2 a_uv;
in vec3 a_normL;

out vec2 v_uv;
out vec3 v_normW;
out vec3 v_posW;

uniform mat4 u_W;
uniform mat4 u_WVP;

void main()
{
	gl_Position = u_WVP * vec4(a_posL, 1.0);

	v_uv = a_uv;
	v_normW = vec3(u_W * vec4(a_normL, 0.0));
	v_posW = vec3(u_W * vec4(a_posL, 1.0));
}
