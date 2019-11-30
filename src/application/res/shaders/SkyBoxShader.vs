in vec3 a_posL;
out vec3 v_posL;

uniform mat4 u_WVP;

void main()
{
	gl_Position = u_WVP * vec4(a_posL, 1.0);
	v_posL = a_posL;
}
