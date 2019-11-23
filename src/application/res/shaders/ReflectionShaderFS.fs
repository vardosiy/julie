precision mediump float;

varying vec3 v_toEye;
varying vec3 v_normW;

uniform samplerCube u_cubeTexture;

void main()
{
	vec3 reflectDir = reflect(normalize(v_toEye), normalize(v_normW));

	gl_FragColor = textureCube(u_cubeTexture, normalize(reflectDir));
}
