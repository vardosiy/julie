#include "ConvertingHelper.hpp"

#include "renderer/TextureTiling.hpp"
#include "renderer/TextureFilteringMode.hpp"

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

s32 filteringModeToGlValue(TextureFilteringMode _mode) noexcept
{
	switch (_mode)
	{
		case TextureFilteringMode::Nearest:				return GL_NEAREST;
		case TextureFilteringMode::Linear:				return GL_LINEAR;
		case TextureFilteringMode::LinearMipmapLinear:	return GL_LINEAR_MIPMAP_LINEAR;
	}

	ASSERT(0);
	return 0;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
