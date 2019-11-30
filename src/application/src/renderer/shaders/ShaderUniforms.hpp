#pragma once

struct ShaderUniforms
{
	int u_WVP;

	int u_W;
	int u_camPosition;

	int u_fogStart;
	int u_fogRange;
	int u_fogColor;

	int u_tilingFactor;
	int u_dMax;
	int u_depthDispl;
	int u_depthAdjust;
	int u_color;

	int u_ambientWeight;
	int u_ambientColor;
	int u_specularPower;

	int u_dirLightColor;
	int u_pointLightColor;
	int u_lightDirection;
	int u_lightPosition;

	int u_time;

	int u_texture2D;
	int u_cubeTexture;

	int u_step;
	int u_limit;

	int u_near;
	int u_far;
	int u_clarity;
	int u_fade;
};
