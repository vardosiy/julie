#version 330 core
#extension GL_NV_shadow_samplers_cube : enable
precision mediump float;

in vec3 v_posL;
out vec4 o_color;

uniform samplerCube u_cubeTexture;

void main()
{
	o_color = textureCube(u_cubeTexture, v_posL);
}
