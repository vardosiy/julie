#version 330 core
#extension GL_NV_shadow_samplers_cube : enable
precision mediump float;

in vec3 v_toEye;
in vec3 v_normW;
out vec4 o_color;

uniform samplerCube u_cubeTexture;

void main()
{
	vec3 reflectDir = reflect(normalize(v_toEye), normalize(v_normW));

	o_color = textureCube(u_cubeTexture, normalize(reflectDir));
}
