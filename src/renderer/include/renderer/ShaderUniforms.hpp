#pragma once

#include "renderer/Types.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

struct ShaderUniforms
{
	s32 u_WVP;

	s32 u_W;
	s32 u_camPosition;

	s32 u_fogStart;
	s32 u_fogRange;
	s32 u_fogColor;

	s32 u_tilingFactor;
	s32 u_dMax;
	s32 u_depthDispl;
	s32 u_depthAdjust;
	s32 u_color;

	s32 u_ambientWeight;
	s32 u_ambientColor;
	s32 u_specularPower;

	s32 u_dirLightColor;
	s32 u_pointLightColor;
	s32 u_lightDirection;
	s32 u_lightPosition;

	s32 u_time;

	s32 u_texture2D;
	s32 u_cubeTexture;

	s32 u_step;
	s32 u_limit;

	s32 u_near;
	s32 u_far;
	s32 u_clarity;
	s32 u_fade;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
