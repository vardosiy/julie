precision mediump float;

varying vec3 v_posL;

uniform samplerCube u_cubeTexture;

void main()
{
	gl_FragColor = textureCube(u_cubeTexture, v_posL);
}
