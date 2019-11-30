precision mediump float;

in vec3 v_toEye;
in vec3 v_normW;

uniform samplerCube u_cubeTexture;

void main()
{
	vec3 reflectDir = reflect(normalize(v_toEye), normalize(v_normW));

	gl_FragColor = textureCube(u_cubeTexture, normalize(reflectDir));
}
