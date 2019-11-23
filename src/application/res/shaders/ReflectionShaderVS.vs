attribute vec3 a_posL;
attribute vec3 a_normL;

varying vec3 v_toEye;
varying vec3 v_normW;

uniform mat4 u_WVP;
uniform mat4 u_W;
uniform vec3 u_camPosition;

void main()
{
	gl_Position = u_WVP * vec4(a_posL, 1.0);

	v_toEye = vec3(u_W * vec4(a_posL, 1.0)) - u_camPosition;
	v_normW = vec3(u_W * vec4(a_normL, 0.0));
}
