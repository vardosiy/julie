precision mediump float;

in vec3 v_posL;

uniform samplerCube u_cubeTexture;

void main()
{
	gl_FragColor = textureCube(u_cubeTexture, v_posL);
}
