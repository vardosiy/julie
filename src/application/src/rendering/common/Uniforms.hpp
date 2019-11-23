#pragma once

#include <glad/glad.h>

struct Uniforms
{
	GLint u_WVP;

	GLint u_W;
	GLint u_camPosition;

	GLint u_fogStart;
	GLint u_fogRange;
	GLint u_fogColor;

	GLint u_tilingFactor;
	GLint u_dMax;
	GLint u_depthDispl;
	GLint u_depthAdjust;
	GLint u_color;

	GLint u_ambientWeight;
	GLint u_ambientColor;
	GLint u_specularPower;

	GLint u_dirLightColor;
	GLint u_pointLightColor;
	GLint u_lightDirection;
	GLint u_lightPosition;

	GLint u_time;

	GLint u_texture2D;
	GLint u_cubeTexture;

	GLint u_step;
	GLint u_limit;

	GLint u_near;
	GLint u_far;
	GLint u_clarity;
	GLint u_fade;
};
