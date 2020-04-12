#include "ConvertingHelper.hpp"

#include "renderer/TextureTiling.hpp"
#include "renderer/TextureFiltering.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

float tilingToGlValue(TextureTiling _tiling) noexcept
{
	switch (_tiling)
	{
		case TextureTiling::ClampToEdge:	return GL_CLAMP_TO_EDGE;
		case TextureTiling::Repeat:			return GL_REPEAT;
		case TextureTiling::MirroredRepeat:	return GL_MIRRORED_REPEAT;
	}

	ASSERT(0);
	return 0.0f;
}

//-----------------------------------------------------------------------------

s32 filteringToGlValue(TextureFiltering _mode) noexcept
{
	switch (_mode)
	{
		case TextureFiltering::Nearest:				return GL_NEAREST;
		case TextureFiltering::Linear:				return GL_LINEAR;
		case TextureFiltering::LinearMipmapLinear:	return GL_LINEAR_MIPMAP_LINEAR;
	}

	ASSERT(0);
	return 0;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
